//int multiply (int a, int  b) {
//	return a * b;
//}
int addition (int a, int b) {
	return a + b;
}

int subtraction(int a, int b) {
	return addition(b, a);
}

int main  () {
	//+ addition(5, 11) + subtraction(5, 11) + 20;
	return subtraction(20, 10);
}
