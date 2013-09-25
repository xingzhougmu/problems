
#include <stdio.h>
#include <stdlib.h>
#include <map>
#include <list>
#include <iostream>

#include "Bitmap.h"

using namespace std;


// using map
void findLongestSubset(int input[], int arraySize, int* maxLen, int* start)
{
	map<int, int> countMap;
	*maxLen = 1;
	*start = input[0];
	for(int i=0; i<arraySize; i++){
		if (!countMap[input[i]]){ // if current number does not exist in the map
			countMap[input[i]] = 1;
			if (countMap[input[i]-1]){ // if before exists
				countMap[input[i]-1]++;
				countMap[input[i]] = countMap[input[i]-1];
				if (countMap[input[i]] > *maxLen){
					*maxLen = countMap[input[i]];
					*start = input[i]-1; 
				}
			}

			if (countMap[input[i]+1]){ // if behind exists
				int behindCount = countMap[input[i]+1];
				countMap[input[i]+behindCount] +=countMap[input[i]];
				countMap[input[i]] = countMap[input[i]+behindCount];
				if (countMap[input[i]+behindCount] > *maxLen){
					*maxLen = countMap[input[i]+behindCount];
					*start = input[i];
				}
				if (countMap[input[i]-1]){ // update before list
					int beforeCount = countMap[input[i]-1];
					countMap[input[i]-behindCount+1] =countMap[input[i]];
					*start = input[i] - behindCount;
				}
			}
		}
	}
}

void printSequence(int start, size_t length){
	cout << "max length: " << length << endl;
	while (length--)
		cout << start++ << " ";
	cout << endl;
}

// another map version: http://www.cppblog.com/everyday/articles/201439.html
int find_longest_consecutive_items(int* list, int size){
	map<int, int> mapping;
	int max = 1;
	int start = list[0];

	for (int i=0; i<size; i++){
		if (mapping.find(list[i]) == mapping.end()){
			int cur = list[i];
			int cur_start = cur;
			mapping.insert(make_pair(cur, 1));

			map<int, int>::iterator pre = mapping.find(cur - 1);
			map<int, int>::iterator next = mapping.find(cur + 1);

			if (pre != mapping.end()){
				mapping[cur] = pre->second + 1;
				//pre->second = mapping[cur];
			}

			if (next != mapping.end()){
				int last = next->first + next->second -1;
				mapping[last] = mapping[cur] = mapping[cur] + mapping[last];
				if (pre != mapping.end()){
					int first = pre->first - pre->second + 1;
					mapping[first] = mapping[cur];
					cur_start = first;
				}
			}

			if (mapping[cur_start] > max){
				start = cur_start;
				max = mapping[cur_start];
			}
		}
	}

	cout << "Longest Consecutive items:";
	for (int i=0; i<max; i++)
		cout << " " << start+i;
	cout << endl;

	return max;
	
}

void find_min_max(int* list, size_t length, int* min, int* max){
	for(int i=0; i<length; i++){
		if (list[i] < *min)
			*min = list[i];
		if (list[i] > *max)
			*max = list[i];
	}
}

int find_longest_sequence_bitmap(int* list, size_t length){
	Bitmap bitmap;
	int min = list[0];
	int max = list[0];
	find_min_max(list, length, &min, &max);
	bitmap.init(max-min+1,min);

	for (int i=0; i<length; i++)
		bitmap.set(list[i]);

	int start = -1;
	int maxLen = 0;
	int curr_start = -1;
	int curr_maxLen = 0;

	for (int i= min; i<=max; i++){
		if (bitmap.get(i)){   // if have this number
			++curr_maxLen;
			if (curr_start == -1){
				curr_start = i;
			}
		}
		else{			
			if (curr_maxLen > maxLen){ // update maxLen
				start = curr_start;
				maxLen = curr_maxLen;				
			}
			curr_start = -1;
			curr_maxLen = 0;
		}
	}

	if (curr_maxLen > maxLen){ //update maxLen
		start = curr_start;
		maxLen = curr_maxLen;				
	}
	bitmap.free();

	cout << "Longest Consecutive items - bitmap:";
	for (int i=0; i<maxLen; i++)
		cout << " " << start+i;
	cout << endl;

	return maxLen;	
}


int main(int argc, char* argv[])
{
	int inputArray[] = {15, 7, 12, 6, 14, 13, 9, 11};
	int maxLen = 0;
	size_t arraySize = sizeof(inputArray) / sizeof(int);
	int start;

	findLongestSubset(inputArray, arraySize, &maxLen, &start);
	printSequence(start, maxLen);

	cout << "***********************" << endl;
	find_longest_consecutive_items(inputArray, arraySize);

	cout << "*Bitmap*************" << endl;
	find_longest_sequence_bitmap(inputArray, arraySize);

	int pause;
	cin >> pause;
	return 0;
}

