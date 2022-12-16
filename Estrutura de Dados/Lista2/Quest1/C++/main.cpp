#include <cstdio>
#include <vector>

using namespace std;

bool crisis(int number_of_regions, int m)
{
    int position = 0;

    vector<int> regions;

    for(int i = 1; i <= number_of_regions; i++)
        regions.push_back(i);


    do{
        // printf("v.begin() + position = %d + %d = %d\n", v.begin(), position, v.begin() + position);

        regions.erase(regions.begin() + position);
        position = (position - 1 + m) % regions.size();

    }while(regions.size() > 1);

    return (regions[0] == 13);
}

int main(void)
{
 int number_of_regions, m;

 while(scanf("%d", &number_of_regions) && number_of_regions)
 {
  m = 1;
  while(!crisis(number_of_regions, m))
   m++;

  printf("%d\n", m);
 }

 return 0;
}