"""
Thin wrapper around ADB (Android Debug Bridge)

Adopted from https://github.com/BennbuildVGC/android_controller/blob/master/android_controller/android_controller.py
"""

import subprocess


def check_connections():
    process = subprocess.Popen(
        ["adb", "devices"], stdout=subprocess.PIPE, stderr=subprocess.PIPE
    )
    output = process.stdout.read().decode("utf-8")
    output = output.replace("\r", "")
    output = output.split("\n")
    value = []
    for connection in output[1:]:
        if connection == "":
            continue
        connection = connection.split("\t")
        if connection[1] == "device":
            value.append(connection[0])

    return value


def connect(host: str):
    subprocess.run(["adb", "connect", host])


def disconnect(host: str = "all"):
    if host == "all":
        subprocess.run(["adb", "disconnect"])
    else:
        subprocess.run(["adb", "connect", host])


def tap(x: int, y: int):
    subprocess.run(["adb", "shell", "input", "tap", str(x), str(y)])


def swipe(x1: int, y1: int, x2: int, y2: int):
    subprocess.run(
        ["adb", "shell", "input", "swipe", str(x1), str(y1), str(x2), str(y2)]
    )


def key_vent(key: str, longpress: bool = False):
    if longpress:
        subprocess.run(["adb", "shell", "input", "--longpress", key])
    else:
        subprocess.run(["adb", "shell", "input", key])


def capture_screen(png: str):
    """Take screenshot and save to file"""
    with open(png, "w") as hf:
        subprocess.run(["adb", "exec-out", "screencap", "-p"], stdout=hf)

def get_screen():
    """Screenshot as binary PNG"""
    return subprocess.check_output(["adb", "exec-out", "screencap", "-p"])

