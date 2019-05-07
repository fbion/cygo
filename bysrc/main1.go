package main

import (
	"gopp"
	"io/ioutil"
	"log"
	"os"
)

var fname string

func main() {
	if len(os.Args) < 2 {
		log.Fatalln("must specify a go source file to tranpiler")
	}
	fname = os.Args[1]

	psctx := NewParserContext(fname)
	err := psctx.Init()
	gopp.ErrPrint(err)

	g2n := g2nc{}
	g2n.psctx = psctx
	g2n.genpkgs()
	code := g2n.code()
	code = "#include <cxrtbase.h>\n\n" + code
	ioutil.WriteFile("opkgs/foo.c", []byte(code), 0644)
}