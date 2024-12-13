package main

import (
	"A_DS_CW/Graph"
	"bufio"
	"fmt"
	"os"
	"os/exec"
	"runtime"
	"strconv"
	"strings"
)

func clearInputBuffer() {
	reader := bufio.NewReader(os.Stdin)
	_, _ = reader.ReadString('\n')
}

func ClearScreen() {
	if runtime.GOOS == "windows" {
		cmd := exec.Command("cmd", "/c", "cls")
		cmd.Stdout = os.Stdout
		err := cmd.Run()
		if err != nil {
			return
		}
	}
}

func ParseAdjacencyMatrix(filePath string) (*Graph.Graph, error) {
	file, err := os.Open(filePath)
	if err != nil {
		return nil, err
	}
	defer func(file *os.File) {
		err := file.Close()
		if err != nil {

		}
	}(file)

	scanner := bufio.NewScanner(file)
	scanner.Scan()
	vertices := strings.Fields(scanner.Text())
	numVertices := len(vertices)

	graph := &Graph.Graph{
		V:   numVertices,
		Adj: make(map[string][]Graph.Edge),
	}

	row := 0
	for scanner.Scan() {
		line := scanner.Text()
		weights := strings.Fields(line)
		for col, weightStr := range weights {
			weight, err := strconv.Atoi(weightStr)
			if err != nil {
				return nil, fmt.Errorf("invalid weight at row %d, col %d: %v", row+1, col+1, err)
			}
			if weight > 0 {
				src := vertices[row]
				dest := vertices[col]
				graph.AddEdge(src, dest, weight)
			}
		}
		row++
	}

	if err := scanner.Err(); err != nil {
		return nil, err
	}

	return graph, nil
}

func printMenu() {
	fmt.Println("Main menu:")
	fmt.Println("1. Make Graph")
	fmt.Println("2. Graph traversal")
	fmt.Println("3. Find Min-Spanning Tree")
	fmt.Println("4. Print Graph")
	fmt.Println("5. Clear screen")
	fmt.Println("6. Exit")
}

func application() {
	var choice int
	var filename string
	var graph *Graph.Graph
	printMenu()
	for {
		fmt.Print("Enter your choice: ")
		_, err := fmt.Scanln(&choice)
		if err != nil {
			fmt.Println("Invalid input. Please enter a number.")
			continue
		}
		switch choice {
		case 1:
			// filename - Adjacency_matrix.txt
			fmt.Print("Enter filename: ")
			_, err = fmt.Scanln(&filename)
			if err != nil {
				fmt.Println("Error reading filename")
				continue
			}
			graph, err = ParseAdjacencyMatrix(filename)
			if err != nil {
				fmt.Printf("Error parsing adjacency matrix: %v\n", err)
				continue
			}
		case 2:
			fmt.Println("1) DFS")
			fmt.Println("2) BFS")
			fmt.Print("Enter your choice: ")
			_, err = fmt.Scanln(&choice)
			if err != nil {
				fmt.Println("Invalid input. Please enter a number.")
				continue
			}
			if choice == 1 {
				fmt.Print("DFS: ")
				graph.DFS()
				clearInputBuffer()
			} else if choice == 2 {
				fmt.Print("BFS: ")
				graph.BFS("A")
				clearInputBuffer()
			}
		case 3:
			graph.FindMinSpanningTree()
		case 4:
			fmt.Println("Graph:")
			graph.Print()
		case 5:
			ClearScreen()
			printMenu()
		case 6:
			return
		}
	}
}
