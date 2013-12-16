#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <bitset>

using namespace std;


const int MAX = 1000000000 + 1;
bitset<MAX> Board1Set;
bitset<MAX> Board2Set;


int main()
{
    int T;
    cin >> T;

    for (int Case = 1; Case <= T; ++Case)
    {
        int N, M;
        cin >> N >> M;

        vector<unsigned long long> Board1(N);
        vector<unsigned long long> Board2(M);

        unsigned long long x1, a1, b1, c1, r1;
        cin >> x1 >> a1 >> b1 >> c1 >> r1;

        unsigned long long x2, a2, b2, c2, r2;
        cin >> x2 >> a2 >> b2 >> c2 >> r2;

        Board1[0] = x1;
        Board2[0] = x2;
        for (int i = 1; i < max(N, M); ++i)
        {
            if (i < N)
            {
                Board1[i] = (a1 * Board1[(i - 1) % N] + b1 * Board2[(i - 1) % M] + c1) % r1;
            }
            if (i < M)
            {
                Board2[i] = (a2 * Board1[(i - 1) % N] + b2 * Board2[(i - 1) % M] + c2) % r2;
            }
        }

        unsigned long long countPairs = 0;
        int board1Index = 0;
        int board2Index = 0;
        int unequalNumbers = 0;
        Board1Set.reset();
        Board2Set.reset();

        while ((board1Index < N) && (board2Index < M))
        {
            int i;
            unsigned long long numberOne = Board1[board1Index];
            for (i = board1Index + 1; i < N; ++i)
            {
                if ((Board1[i] != numberOne) && (!Board1Set[Board1[i]]))
                {
                    break;
                }
            }

            int j;
            unsigned long long numberTwo = Board2[board2Index];
            for (j = board2Index + 1; j < M; ++j)
            {
                if ((Board2[j] != numberTwo) && (!Board2Set[Board2[j]]))
                {
                    break;
                }
            }

            bool found1 = Board2Set[numberOne];
            bool found2 = Board1Set[numberTwo];

            if (found1 && found2)
            {
                --unequalNumbers;
            }
            else if (!found1 && !found2 && (numberOne != numberTwo))
            {
                ++unequalNumbers;
            }

            if (unequalNumbers == 0)
            {
                countPairs += ((unsigned long long)i - board1Index) * ((unsigned long long)j - board2Index);
            }

            Board1Set.set(numberOne);
            Board2Set.set(numberTwo);
            board1Index = i;
            board2Index = j;
        }

        cout << "Case #" << Case << ": " << countPairs << endl;
    }

    return 0;
}
