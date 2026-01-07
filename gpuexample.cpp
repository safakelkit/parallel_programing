#include <omp.h>
#include <iostream>
using namespace std;

int main() {
  const int n = 16;
  int A[n], B[n], C[n];
  int team_of[n], thread_of[n];

  for (int i = 0; i < n; i++) {
    A[i] = i;
    B[i] = 100 + i;
    C[i] = 0;
    team_of[i] = -1;
    thread_of[i] = -1;
  }

  #pragma omp target map(to: A[0:n], B[0:n]) map(from: C[0:n], team_of[0:n], thread_of[0:n])
  {
    #pragma omp teams
    {
      #pragma omp distribute parallel for
      for (int i = 0; i < n; i++) {
        C[i] = A[i] + B[i];

        // Kim çalıştırdı?
        team_of[i]   = omp_get_team_num();
        thread_of[i] = omp_get_thread_num();
      }
    }
  }

  // Host'ta temiz çıktı
  for (int i = 0; i < n; i++) {
    cout << "i=" << i
         << " team=" << team_of[i]
         << " thread=" << thread_of[i]
         << " C=" << C[i] << "\n";
  }

  return 0;
}
