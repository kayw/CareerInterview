// Package debug
// http://stackoverflow.com/questions/25950873/golang-gdb-print-variables
package debug

import (
	"path"
	"sync"
)

var traceLock sync.Mutex

func trace(a ...interface{}) {
	traceLock.Lock()
	pc, f, ln, ok := runtime.Caller(1)
	fn := ""
	if ok {
		fn = runtime.FuncForPC(pc).Name()
	}
	fmt.Printf("trace: %s %s:%d", fn, filepath.Base(f), ln)
	if len(a) > 0 {
		fmt.Println(append([]interface{}{": "}, a...)...)
	}
	traceLock.Unlock()
}
