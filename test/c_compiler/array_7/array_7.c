int main () {
	int i, sum = 0, pos, neg;
	int arr[9] = {5,-2,3, 0, 6, 9, 12, 20, 7};
	for (i = 0; i < 9; i++) {
		sum += arr[i];
		if (arr[i] > 0)
			pos += arr[i];
		if (arr[i] < 0)
			neg += arr[i];
	}
	return sum;
}
