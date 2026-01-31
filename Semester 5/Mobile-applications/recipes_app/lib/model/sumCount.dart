class SumCount {
  double sum = 0;
  int count = 0;
  void add(double value) {
    sum += value;
    count++;
  }
  double get average => count == 0 ? 0 : sum / count;
}
