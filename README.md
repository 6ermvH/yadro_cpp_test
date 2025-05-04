# PC club manager
Программа написана на С++20 с использованием системы сборки make, unit тесты реализованы с помощью gtest, integration тесты запускаются Go скриптом.
## build
- ```make``` -> бинарник `main`
- ```make test``` -> бинарник `test`
- ```go build -o intgr_test ./test.gp``` -> бинарник `intgr_test`
## deploy
- ```./main <FILE PATH>```
