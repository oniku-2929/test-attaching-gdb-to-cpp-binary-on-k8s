# test-attaching-gdb-to-cpp-binary-on-k8s

## Description
test attaching gdb to c++ binary which is working as container in Kubernetes environment.  
gdb container works as side car container.  
two containers will build as Docker container and working on k8s Deployments.  
  
testapp:  
a simple C++ binary works on this container. the binary is debug target.
  
debugtool:  
gdb is installed on this container. source file and binary are copied this container.(for using gdb) 

## Usage
When start containers
```
git clone git@github.com:iwana2929/test-attaching-gdb-to-cpp-binary-on-k8s.git
./build.sh
kubectl apply -f deployment.yaml
```

When check attaching gdb to app process which is working in testapp container.
```
kubectl get pod  
(check that working gdb-attach-test-deployment)  
kubectl exec -it gdb-attach-test-deployment-... -c debugtool /bin/bash  

(in container bash terminal)
ps -ef 
(check process id of /home/app )
gdb -p {PID} 

(in gdb command)
(gdb) b app.cpp:SignalHandler::handleSignal (example)
(gdb) continue

(open other terminal)
kubectl exec -it gdb-attach-test-deployment-... -c debugtool /bin/bash

(in container bash terminal)
kill {PID} SIGTERM

it can catch the signal and can stop on breakpoints.
```

When stop containers
```
kubectl delete -f deployment.yaml
```

## Licence
[MIT](https://github.com/tcnksm/tool/blob/master/LICENCE)
