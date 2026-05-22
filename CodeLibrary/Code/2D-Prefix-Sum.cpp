pf[i][j] += pf[i - 1][j] + pf[i][j - 1] - pf[i - 1][j - 1];
// retrieve pfsum from (u, l) to (d, r)
pf[d][r] - pf[u - 1][r] - pf[d][l - 1] + pf[u - 1][l - 1];