typedef map<char, unsigned> FreqTable;
typedef vector< pair<char, unsigned> > FreqVector;

FreqTable counts(string);
FreqVector reshape(FreqTable);
void quick_sort(FreqVector &, int start = 0, int end = -1);
int partition(FreqVector &, int, int);
