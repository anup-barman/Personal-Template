for (auto it = st.begin(); it != st.end(); ) {
  if (temp.find(*it) == temp.end()) {
    st.erase(it++);
  } else {
    ++it;
  }
}