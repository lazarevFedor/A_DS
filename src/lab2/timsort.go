package main

import (
	"container/list"
)

func getMinRunLength(n int) int {
	flag := 0
	for n >= 64 {
		flag |= n & 1
		n >>= 1

	}
	return n + flag
}

func BinarySearch(array []int, element int) int {
	left, right := 0, len(array)-1
	for left <= right {
		mid := (left + right) / 2
		if array[mid] < element {
			left = mid + 1
		} else {
			right = mid - 1
		}
	}
	return left
}

func InsertionSort(array []int) []int {
	for i := 1; i < len(array); i++ {
		key := array[i]
		j := i - 1
		for j >= 0 && array[j] > key {
			array[j+1] = array[j]
			j--
		}
		array[j+1] = key
	}
	return array
}

func ReverseArray(array []int) []int {
	left, right := 0, len(array)-1
	for left < right {
		if array[left] > array[right] {
			array[left], array[right] = array[right], array[left]
		}
		left++
		right--
	}
	return array
}

func MergeSort(left, right []int) []int {
	res := make([]int, 0)
	leftCount, rightCount := 0, 0
	i, j := 0, 0
	gallopCount := 0
	for i < len(left) && j < len(right) {
		if left[i] <= right[j] {
			res = append(res, left[i])
			leftCount++
			rightCount = 0
			i++
			if leftCount == 7 {
				gallopCount++
				pos := BinarySearch(left[i:], right[j])
				tmp := i
				for index := 0; index < pos; index++ {
					res = append(res, left[tmp+index])
					i++
				}
				leftCount = 0
			}
		} else {
			res = append(res, right[j])
			j++
			rightCount++
			leftCount = 0
			if rightCount == 3 {
				gallopCount++
				pos := BinarySearch(right[j:], left[i])
				tmp := j
				for index := 0; index < pos; index++ {
					res = append(res, right[tmp+index])
					j++
				}
				rightCount = 0
			}
		}
	}
	res = append(res, left[i:]...)
	res = append(res, right[j:]...)
	return res
}

func MergeBlocs(blocs *list.List) []int {
	stack := list.New()
	for blocs.Len() > 0 {
		stack.PushFront(blocs.Front().Value.([]int))
		blocs.Remove(blocs.Front())
	}
	for stack.Len() >= 2 {
		if stack.Len() >= 3 {
			var x, y, z []int
			x = stack.Front().Value.([]int)
			stack.Remove(stack.Front())
			y = stack.Front().Value.([]int)
			stack.Remove(stack.Front())
			z = stack.Front().Value.([]int)
			stack.Remove(stack.Front())
			X, Y, Z := len(x), len(y), len(z)
			if Z > (X+Y) && Y > X {
				stack.PushFront(z)
				stack.PushFront(y)
				stack.PushFront(x)
				break
			}
			if X <= Z {
				merged := MergeSort(y, x)
				stack.PushFront(z)
				stack.PushFront(merged)
			} else {
				merged := MergeSort(z, y)
				stack.PushFront(merged)
				stack.PushFront(x)
			}
		} else {
			var x, y []int
			x = stack.Front().Value.([]int)
			stack.Remove(stack.Front())
			y = stack.Front().Value.([]int)
			stack.Remove(stack.Front())
			X, Y := len(x), len(y)
			if Y > X {
				stack.PushFront(y)
				stack.PushFront(x)
				break
			}
			merged := MergeSort(y, x)
			stack.PushFront(merged)
		}
	}
	for stack.Len() > 1 {
		if stack.Len() >= 3 {
			var x, y, z []int
			x = stack.Front().Value.([]int)
			stack.Remove(stack.Front())
			y = stack.Front().Value.([]int)
			stack.Remove(stack.Front())
			z = stack.Front().Value.([]int)
			stack.Remove(stack.Front())
			X, Z := len(x), len(z)
			if X <= Z {
				merged := MergeSort(y, x)
				stack.PushFront(z)
				stack.PushFront(merged)
			} else {
				merged := MergeSort(z, y)
				stack.PushFront(merged)
				stack.PushFront(x)
			}
		} else {
			var x, y []int
			x = stack.Front().Value.([]int)
			stack.Remove(stack.Front())
			y = stack.Front().Value.([]int)
			stack.Remove(stack.Front())
			merged := MergeSort(y, x)
			stack.PushFront(merged)
		}
	}
	result := stack.Front().Value.([]int)
	return result
}

func Sort(slice []int) []int {
	minRun := getMinRunLength(len(slice))
	index := 0
	runs := list.New()
	run := make([]int, 0)
	FlagLenRun := false
	if len(slice) == 1 {
		return slice
	}
	for index < len(slice) {
		index += 2
		run = slice[index-2 : index]
		if index >= len(slice) {
			if slice[index-2] > slice[index-1] {
				run = ReverseArray(slice)
			}
			runs.PushBack(run)
		}
		if slice[index-2] > slice[index-1] {
			for slice[index-1] > slice[index] {
				run = append(run, slice[index])
				index++
				if index > len(slice)-1 {
					break
				}
			}
		} else if slice[index-2] <= slice[index-1] {
			for slice[index-1] <= slice[index] {
				run = append(run, slice[index])
				index++
				if index > len(slice)-1 {
					break
				}
			}
		}
		for len(run) < minRun && index <= len(slice)-1 {
			FlagLenRun = true
			run = append(run, slice[index])
			index++
		}
		if FlagLenRun == true {
			run = InsertionSort(run)
		} else {
			run = ReverseArray(run)
		}
		runs.PushBack(run)
	}
	return MergeBlocs(runs)
}
