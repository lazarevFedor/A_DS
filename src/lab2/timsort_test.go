package main

import (
	"math/rand"
	"reflect"
	"testing"
)

func TestSort(t *testing.T) {
	cases := []struct {
		name     string
		input    []int
		expected []int
	}{
		{
			name:     "1) Sorted array",
			input:    []int{1, 2, 3, 4, 5},
			expected: []int{1, 2, 3, 4, 5},
		},
		{
			name:     "2) Small random array",
			input:    []int{5, 3, 8, 1, 9, 2, 6, 4, 7},
			expected: []int{1, 2, 3, 4, 5, 6, 7, 8, 9},
		},
		{
			name:     "Reversed array",
			input:    []int{5, 4, 3, 2, 1},
			expected: []int{1, 2, 3, 4, 5},
		},
		{
			name:     "Array with duplicates",
			input:    []int{5, 5, 3, 8, 1, 9, 2, 6, 4, 7, 5, 5, 5, 5, 5},
			expected: []int{1, 2, 3, 4, 5, 5, 5, 5, 5, 5, 5, 6, 7, 8, 9},
		},
		{
			name:     "Array with 64 elements",
			input:    generateRandomArray(64),
			expected: InsertionSort(generateRandomArray(64)),
		},
		{
			name:     "Array with 150 elements",
			input:    generateRandomArray(150),
			expected: InsertionSort(generateRandomArray(150)),
		},
		{
			name:     "Array with 1000 elements",
			input:    generateRandomArray(1000),
			expected: InsertionSort(generateRandomArray(1000)),
		},
		{
			name:     "Array with 10000 elements",
			input:    generateRandomArray(10000),
			expected: InsertionSort(generateRandomArray(10000)),
		},
	}
	for _, tc := range cases {
		t.Run(tc.name, func(t *testing.T) {
			got := Sort(append([]int{}, tc.input...))
			if !reflect.DeepEqual(got, tc.expected) {
				t.Errorf("got %v, want %v", got, tc.expected)
			}
		})
	}
}

func generateRandomArray(n int) []int {
	result := make([]int, n)
	for i := 0; i < n; i++ {
		result[i] = i
	}
	for i := 0; i < n; i++ {
		j := i + rand.Intn(n-i)
		result[i], result[j] = result[j], result[i]
	}
	return result
}
