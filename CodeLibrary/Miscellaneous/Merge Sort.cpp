// use array of elements, if multiple testcase make inv = 0 each time
// int inv = 0;
void merge(int vct[], int l, int m, int r) {
  int left = m - l + 1, right = r - m, lv[left], rv[right];
  for (int i = 0; i < left; i++) {
    lv[i] = vct[l + i];
  }
  for (int i = 0; i < right; i++) {
    rv[i] = vct[m + 1 + i];
  }
  int i = 0, j = 0, to = l;
  while (i < left && j < right) {
    if (lv[i] <= rv[j]) {
      vct[to] = lv[i];
      i++;
    } else {
      vct[to] = rv[j];
      j++;
      // inversion count
      // int pore = left-i; inv+=pore;
    }
    to++;
  }
  while (i < left) {
    vct[to] = lv[i];
    i++;
    to++;
  }
  while (j < right) {
    vct[to] = rv[j];
    j++;
    to++;
  }
}
void merge_sort(int vct[], int l, int r) {
  if (r <= l) return;
  int m = l + ((r - l) / 2);
  merge_sort(vct, l, m);
  merge_sort(vct, m + 1, r);
  merge(vct, l, m, r);
}
