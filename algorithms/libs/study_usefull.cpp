int randArr(int *&arr) {

	int size = rand()%MAX_SIZE;

	arr = new int[size];

	for (int i = 0; i < size; ++i) {
		arr[i] = rand()%MAX_NUM;
	}

	return size;
}