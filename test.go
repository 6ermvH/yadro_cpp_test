package main

// make with copilot

import (
	"bytes"
	"fmt"
	"os"
	"os/exec"
	"path/filepath"
)

func main() {
	update := len(os.Args) > 1 && os.Args[1] == "--update"

	testDir := "test_files/test"
	wantDir := "test_files/want"
	hasDir := "test_files/has"

	files, _ := filepath.Glob(filepath.Join(testDir, "*.txt"))
	for _, test := range files {
		name := filepath.Base(test)
		want := filepath.Join(wantDir, name)
		has := filepath.Join(hasDir, name)

		cmd := exec.Command("./main", test)
		out, err := cmd.Output()
		if err != nil {
			fmt.Printf("❌ %s (run error)\n", name)
			continue
		}

		os.WriteFile(has, out, 0644)

		if update {
			os.WriteFile(want, out, 0644)
			fmt.Printf("🔄 %s updated\n", name)
			continue
		}

		wantData, err := os.ReadFile(want)
		if err != nil {
			fmt.Printf("❌ %s (missing want)\n", name)
			continue
		}

		if bytes.Equal(out, wantData) {
			fmt.Printf("✅ %s\n", name)
		} else {
			fmt.Printf("❌ %s\n", name)
		}
	}
}

