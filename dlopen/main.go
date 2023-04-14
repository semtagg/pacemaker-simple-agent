package main

import "C"

import (
	"fmt"
	"log"
	"os"
)

func WriteMessage(inst, msg string) {
	lg := fmt.Sprintf("/var/log/dlopen/%v.log", inst)
	//lg := "/var/log/dlopen/test.so.log"
	fmt.Println(lg)
	f, err := os.OpenFile(lg, os.O_APPEND|os.O_CREATE|os.O_WRONLY, 0644)
	if err != nil {
		log.Fatal(err)
	}
	if _, err := f.Write([]byte(msg)); err != nil {
		f.Close() // ignore error; Write error takes precedence
		log.Fatal(err)
	}
	if err := f.Close(); err != nil {
		log.Fatal(err)
	}
}

//export start
func start(inst string) int {
	WriteMessage(inst, fmt.Sprintf("Action: start, instance: %s.\n", inst))
	return 0
}

//export stop
func stop(inst string) int {
	WriteMessage(inst, fmt.Sprintf("Action: stop, instance: %s.\n", inst))
	return 0
}

//export status
func status(inst string) int {
	WriteMessage(inst, fmt.Sprintf("Action: status, instance: %s.\n", inst))
	return 0
}

//export monitor
func monitor(inst string) int {
	WriteMessage(inst, fmt.Sprintf("Action: monitor, instance: %s.\n", inst))
	return 0
}

//export metadata
func metadata() string {
	return `<?xml version="1.0"?>
<!DOCTYPE resource-agent SYSTEM "ra-api-1.dtd">
<resource-agent name="test.so" version="1.0">
  <version>1.0</version>
  <longdesc lang="en">
   This script is used to write data to a file.
  </longdesc>
  <shortdesc lang="en">Test agent</shortdesc>
  <actions>
    <action name="start"   timeout="15s" />
    <action name="stop"    timeout="15s" />
    <action name="status"  timeout="15s" interval="15s" />
    <action name="monitor" timeout="15s" interval="15s" />
    <action name="meta-data"  timeout="5s" />
  </actions>
</resource-agent>
`
}

func main() {}

