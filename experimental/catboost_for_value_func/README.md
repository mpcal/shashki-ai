Steps to learn a classifier

0) download catboost and build libcatboostmodel.so from sources
   * build all
   * find sub-project catboostmodel and bulid it
   * copy libcatboostmodel.so over to lib/

1) generate data
   ```
   ../build/shashki_ai gendata
   ```

2) train catboost classifier
   ```
   mkdir -p train_dir
   catboost fit -f libsvm://train.libsvm -t libsvm://test.libsvm --cd train.cd --model-file model.bin --train-dir train_dir --loss-function Logloss --iterations 100
   ```
   will output model to `model.bin`
