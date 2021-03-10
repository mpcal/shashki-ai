'use strict';

console.assert(EMPTY === 0 && BK_MAN === 1 && WT_MAN === 2 && BK_KING === 3 && WT_KING === 4);
const fills = { 0: "black", 1: "black", 2: "white", 3: "black", 4: "white" }
const strokeWidth = { 0: 0, 1: 0, 2: 0, 3: 2, 4: 2 }
const strokes = { 0: "black", 1: "black", 2: "white", 3: "yellow", 4: "yellow" }

var treeData = null;  // tree data, typically from backend
var svg = null;
var root = null;
var d3Nodes = null;  // index by "ref id", get "data for a single board"

const tree = d3.layout.tree().nodeSize(nodeSize)
const diagonal = d3.svg.diagonal().projection(function (d) { return [d.x, d.y]; });

function _fetchBoards() {
  function getValue(id) {
    const txt = document.getElementById(id);
    const value = BigInt(txt.value);
    if (Number.isNaN(value))
      throw RangeError("Bad number: " + value)
    return value;
  }
  const bk = getValue("txtBk");
  const wt = getValue("txtWt");
  const player = document.getElementById("txtPlayer").value;
  if (player.localeCompare("bk") !== 0 && player.localeCompare("wt") !== 0)
    throw RangeError("Player must be 'bk' or 'wt', but was " + player);
  const strat = document.getElementById("txtStrat").value;
  const url = `http://localhost:9080/v1/moves/best/?bk=${bk}&wt=${wt}` +
    `&player=${player}&strat=${strat}&explain=true`;
  console.log("query:", url);

  return fetch(url)
    .then(response => {
      return response.json();
      // response.json().then(value => {
      //   return value;
      // });
    })
    .catch(reason => alert("Fetch failed. Reason:", reason));
}

// bk, wt: BigInt
function _boardToGrid(bk, wt) {

  function to_ix(row, col) {
    return row * 4 + (col >> 1);
  }

  var value = new Array();
  var ypos = 1;

  for (var r = 0; r < 8; r++) {
    var xpos = 1;
    value.push(new Array());
    for (var c = 0; c < 8; c++) {
      // find color value
      var color = EMPTY;
      if ((c + r % 2) % 2 == 1) {
        const man_bit = 1n << BigInt(to_ix(r, c));
        const king_bit = 1n << BigInt((to_ix(r, c) + 32));
        if (bk & man_bit)
          color = BK_MAN;
        else if (wt & man_bit)
          color = WT_MAN;
        else if (bk & king_bit)
          color = BK_KING;
        else if (wt & king_bit)
          color = WT_KING;
      }

      // append cell to row
      value[r].push({
        x: xpos,
        y: ypos,
        width: squareSize,
        height: squareSize,
        dark: (c + r % 2) % 2 == 0,
        color: color,
      })
      xpos += squareSize;
    }
    ypos += squareSize;
  }

  return value;
}

function _update(source) {
  const tic = performance.now()

  // Compute the new tree layout.
  const nodes = tree.nodes(root).reverse();
  const links = tree.links(nodes);

  // Update the nodes...
  var i = 0;
  var node = svg.selectAll("g.node")
    .data(nodes, function (d) { return d.id || (d.id = ++i); });

  // Enter any new nodes at the parent's previous position.
  var nodeEnter = node.enter().append("g")
    .attr("class", "node")
    .attr("transform", function (d) { return "translate(" + source.x0 + "," + source.y0 + ")"; })
    .on("click", _click)

  nodeEnter.append("rect")
    .attr("x", function (d) { return -4 * squareSize + 1; })
    .attr("y", function (d) { return -4 * squareSize + 1; })
    .attr("width", 8 * squareSize)
    .attr("height", 8 * squareSize)
    .style("fill", "#bbb")

  var grid = nodeEnter
    .append("g")
    .attr("transform", function (d) { return "translate(" + -4 * squareSize + "," + -4 * squareSize + ")"; })

  nodeEnter.append("text")
    .text(function (d) {
      if (d.pruned)
        return "(pruned)";
      const ab = "α=" + (Math.abs(d.alpha) > 10000 ? 'lo' : d.alpha) +
        "," + "β=" + (Math.abs(d.beta) > 10000 ? 'hi' : d.beta);
      return ab;
    })
    .attr("dy", -4.2 * squareSize)
    .attr("class", "caption")

  nodeEnter.append("text")
    .text(function (d) {
      const player = d.bk_turn ? "p=bk" : "p=wt";
      const score = (d.pruned ? "s=X" : ("s=" + (d.score)) + " S=" + (d.best || '?'));
      const ix = "child_ix" in d ? "i=" + d.child_ix : "root";
      return player + " " + (d.pruned ? "" : score) + " " + ix;
    })
    .attr("dy", 4.7 * squareSize)
    .attr("class", "caption")

  var row = grid.selectAll()
    .data(d => {
      return d3Nodes[d.ref];
    })
    .enter().append("g")

  row.selectAll()
    .data(function (d) { return d; })
    .enter().append("rect")
    .attr("x", function (d) { return d.x; })
    .attr("y", function (d) { return d.y; })
    .attr("width", function (d) { return d.width; })
    .attr("height", function (d) { return d.height; })
    .style("fill", function (d) { return d.dark ? "#fff" : "#666" })
    .style("stroke-width", 0)
    .style("stroke", "#222")
    .style("opacity", 0.75);

  row.selectAll()
    .data(function (d) { return d; })
    .enter().append("circle")
    .attr("class", "circles")
    .attr("cx", function (d) { return d.x + squareSize / 2; })
    .attr("cy", function (d) { return d.y + squareSize / 2; })
    .attr("r", d => squareSize / 2 - 2)
    .style("fill", d => fills[d.color])
    .style("opacity", d => d.color === EMPTY ? 0 : 1)
    .style("stroke-width", d => strokeWidth[d.color])
    .style("stroke", d => strokes[d.color])

  // Transition nodes to their new position.
  var nodeUpdate = node.transition()
    .duration(duration)
    .attr("transform", function (node) {
      return "translate(" + node.x + "," + node.y + ")";
    });

  nodeUpdate.select("text")
    .style("fill-opacity", 1);

  // Transition exiting nodes to the parent's new position.
  var nodeExit = node.exit().transition()
    .duration(duration)
    .attr("transform", function (node) {
      return "translate(" + source.x + "," + source.y + ")";
    })
    .remove();

  nodeExit.select("circle")
    .attr("r", 1e-6);

  nodeExit.select("text")
    .style("fill-opacity", 1e-6);

  // Update the links…
  var link = svg.selectAll("path.link")
    .data(links, function (d) { return d.target.id; });

  // Enter any new links at the parent's previous position.
  link.enter().insert("path", "g")
    .attr("class", "link")
    .attr("d", function (d) {
      var o = { x: source.x0, y: source.y0 };
      return diagonal({ source: o, target: o });
    });

  // Transition links to their new position.
  link.transition()
    .duration(duration)
    .attr("d", diagonal);

  // Transition exiting nodes to the parent's new position.
  link.exit().transition()
    .duration(duration)
    .attr("d", function (d) {
      var o = { x: source.x, y: source.y };
      return diagonal({ source: o, target: o });
    })
    .remove();

  // Stash the old positions for transition.
  nodes.forEach(function (d) {
    d.x0 = d.x;
    d.y0 = d.y;
  });

  console.log("_update() elapsed", (performance.now() - tic) / 1000, "sec");
}

// Toggle children on click.
function _click(d) {
  if (d.children) {
    d._children = d.children;
    d.children = null;
  } else {
    d.children = d._children;
    d._children = null;
  }
  _update(d);
}

function _collapse_all() {
  function collapse(d) {
    if (d.children) {
      d._children = d.children;
      d.children = null;
      d._children.forEach(collapse);
    }
  }
  root.children.forEach(collapse);
  _update(root);
}

function runViz() {
  // complex function with two concerns in one:
  // - create d3Nodes: list of d3 board arrays, indexed by `ref`
  // - inject `ref` into tree data (typically coming from backend), effectively
  //   linking board viz (d3Nodes) and tree structure (tree data)
  d3Nodes = [];
  function makeD3Tree(obj) {
    obj["ref"] = d3Nodes.length;
    d3Nodes.push(_boardToGrid(BigInt(obj["bk"]), BigInt(obj["wt"])));
    if ("children" in obj)
      obj["children"].map(makeD3Tree);
  }

  // find tree depth
  var maxDepth = 0;
  function treeStats(obj, depth = 1) {
    if (depth > maxDepth)
      maxDepth = depth;
    if ("children" in obj)
      obj["children"].forEach(function (c) {
        treeStats(c, depth + 1);
      });
  }

  _fetchBoards().then(resp => {
    root = resp.explanation;
    // root = artificialTreeData;  // !! hack, remove

    makeD3Tree(root);
    treeStats(root);

    // fill globals for _update() -- beautiful, isn't it? :/
    const width = 64000;  // just sth really big
    const height = maxDepth * nodeSize[1];
    d3.select("#svg-container svg").remove();
    svg = d3.select("#svg-container").append("svg")
      .attr("width", width)
      .attr("height", height)
      .append("g")
      .attr("transform", "translate(" + width / 2 + "," + 6 * squareSize + ")");
    root.x0 = 0;
    root.y0 = 0;
    _update(root);

    _collapse_all();

    const vw = Math.max(document.documentElement.clientWidth || 0, window.innerWidth || 0)
    window.scrollTo(width / 2 - vw / 2, 0);
  });
}

