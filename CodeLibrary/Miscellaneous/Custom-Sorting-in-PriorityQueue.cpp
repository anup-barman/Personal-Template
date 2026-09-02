auto comp = [](auto &a, auto &b) {
    if (a[0] != b[0]) return a[0] < b[0];
    return a[1] > b[1];
};
priority_queue<T, vector<T>, decltype(comp)> pq(comp);

// comp(a,b) = true → a has lower priority.
// top() = highest-priority element.
// decltype(comp) gets the lambda's type.