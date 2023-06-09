
class Metrics {
public:
  Metrics() {
    // Needs to support default construction.
    mean_ = 0;
    stddev_ = 0;
  }
  Metrics(const std::vector<double> &scores) {
    CHECK(scores.size() > 1);
    double sum = 0;
    for (double score : scores) {
      sum += score;
    }
    mean_ = sum / scores.size();

    // Sample variance = S_x (x - mean)^2 / (N - 1)
    double variance = 0;
    for (double score : scores) {
      variance += std::pow(score - mean_, 2);
    }
    variance /= (scores.size() - 1);
    stddev_ = sqrt(variance);
  }

  double score() const { return mean_ - stddev_; }
  double mean() const { return mean_; }
  double stddev() const { return stddev_; }

  bool operator<(const Metrics &other) const {
    return this->score() < other.score();
  }
  bool operator>(const Metrics &other) const {
    return this->score() > other.score();
  }

private:
  double mean_;
  double stddev_;
};

std::ostream &operator<<(std::ostream &s, const Metrics &metrics) {
  // Not really printing to the stream but good enough for now.
  printf("%.1f (%.1f - %.1f)", metrics.score(), metrics.mean(),
         metrics.stddev());
  return s;
}
