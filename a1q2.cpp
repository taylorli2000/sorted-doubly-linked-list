bool candidate(int array[],int& myCandidate, int sz);
bool majorityElement(const int arr[], int& majority, int sz);

//This function accepts an int array, int and int, and finds the majority element in the array.
//It returns true if there is a majority element. If there isn't, it returns false.
//In both cases, it will also return the majority variable back with the return value.
bool majorityElement(const int arr[], int& majority, int sz) {
	bool rc = false;
	int temp[sz];
	for (int i = 0; i < sz; i++) {
		temp[i] = arr[i];
	}
	if (candidate(temp, majority, sz)) {
		int count = 0;
		for (int i = 0; i < sz && rc == false; i++) {
			if (arr[i] == majority) {
				count++;
			}
			if (count > sz / 2) {
				rc = true;
			}
		}
	}
	return rc;
}
//This function accepts an int array, int and int, and finds candidates for majority element in the array.
//It returns true if there is a majority element. If there isn't, it returns false.
//In both cases, it will also return the myCandidate variable back with the return value.
bool candidate(int array[],int& myCandidate, int sz) {
	bool rc = false;
	bool odd = (sz % 2 == 1);
	int oddCandidate = 0;
	if (odd) {
		oddCandidate = array[--sz];
	}
	int numCandidates = 0;
	for (int i = 0; i < sz; i+=2) {
		if (array[i] == array[i+1]) {
			array[numCandidates++] = array[i];
		}
	}
	if (numCandidates == 1) {
		myCandidate = array[0];
		rc = true;
	}
	else if (numCandidates > 0 && candidate(array, myCandidate, numCandidates)) {
		rc = true;
	}
	else {
		myCandidate = oddCandidate;
		rc = odd;
	}
	return rc;
}
