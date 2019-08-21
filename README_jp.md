# test-attaching-gdb-to-cpp-binary-on-k8s

## 説明
Kubernetes環境でgdbをコンテナで動いているC++バイナリにアタッチするテスト(サイドカーパターン)

gdbが動作しているコンテナはサイドカーとして動作します。  
２つのコンテナがDockerコンテナとして、単一Deployments内で動作します  
  
testapp:  
簡易なC++バイナリが動作しているコンテナです。このバイナリがデバッグターゲットです。
  
debugtool:  
gdbはこのコンテナにインストールされています。ソースと実行バイナリもコピーされています。

## 使用方法
コンテナを動作させるとき
```
git clone git@github.com:iwana2929/test-attaching-gdb-to-cpp-binary-on-k8s.git
./build.sh
kubectl apply -f deployment.yaml
```

gdbをtestappコンテナ内で動作しているappのプロセスにアタッチする時
```
kubectl get pod  
(check that working gdb-attach-test-deployment)  
kubectl exec -it gdb-attach-test-deployment-... -c debugtool /bin/bash  

(bash terminal内で)
ps -ef 
(/home/appのPIDを確認してください)
gdb -p {PID} 

(gdb コマンド)
(gdb) b app.cpp:SignalHandler::handleSignal (breakpointは任意の位置にどうぞ)
(gdb) continue

(他のターミナルを開いて)
kubectl exec -it gdb-attach-test-deployment-... -c debugtool /bin/bash

(更に別のbash terminal内で)
kill {PID} SIGTERM

元々動作していたterminal(gdb)でsignalをキャッチしているのが確認できます
```

コンテナを停止する時
```
kubectl delete -f deployment.yaml
```

## ライセンス
[MIT](https://github.com/tcnksm/tool/blob/master/LICENCE)
