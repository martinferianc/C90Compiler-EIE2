int main () {
	int x = 120;
	int y = 213;

	int z = (x != y) || (x != y);

	int t = 0;

	int h = t || z || x;

    return h;
}
