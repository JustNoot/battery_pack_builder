#include <math.h>
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <random>

int main()
{
    int s, p;
    int cellnum = 0;
    int index = 0;
    int delta = 9999;
    int delta_max = 0;
    int delta_opt;
    char c;
    bool write = false;
    unsigned int dc = 0;

    std::cout << "How many cells in series?\n";
    std::cin >> s;
    std::cout << "How many cells in paralell?\n";
    std::cin >> p;
    cellnum = s * p;
    std::cout << s << "s" << p << "p configuration using " << cellnum << " cells\n";
    std::cout << "Biggest desired delta between cell groups?\n";
    std::cin >> delta_opt;
    std::cout << "Write every try to a file?\n";
    std::cin >> c;
    if ((c=='1') || (c=='y') || (c=='Y')) write = true;
    std::cout << std::endl;

    int sum[s];
    int bat[s][p];
    int mah[cellnum];
    int used[cellnum];
    int number[cellnum];

    std::ifstream battery("battery.txt");
    if (battery.is_open())
    {
        for(int i=0; i<cellnum; i++)
            battery >> mah[i];
        battery.close();
    }

    while(delta>delta_opt)
    {
        for (int i=0; i<cellnum; i++) used[i]=-1;
        index = 0;
        for (int i=0; i<s; i++) sum[i]=0;
        delta_max = 0;

        while(used[cellnum-1]==-1)
        {
            srand(time(NULL));
            for(int i=0; i<cellnum; i++)
                number[i] = std::rand() % cellnum;

            for(int i=0; i<cellnum; i++)
            {
                int bad = 0;
                for (int j=0; j<cellnum; j++)
                    if(number[i] == used[j]) bad++;
                if(!bad)
                {
                    used[index] = number[i];
                    index++;
                }
            }
        }

        for(int i=0; i<s; i++)
            for(int j=0; j<p; j++)
                bat[i][j] = mah[used[j+p*i]];

        for(int i=0; i<s; i++)
            for(int j=0; j<p; j++)
                sum[i] += bat[i][j];

        for(int i=0; i<s; i++)
            for(int j=0; j<s; j++)
                if(delta_max<abs(sum[i]-sum[j])) delta_max=abs(sum[i]-sum[j]);

        dc++;

        if (delta>delta_max) delta=delta_max;
        std::cout << dc << ". delta: " << delta_max << " mAh\n";

        if(write)
        {
            std::ofstream tries("tries.txt", std::ofstream::out | std::ofstream::app);
            if (tries.is_open())
            {
                tries << dc << ". delta: " << delta_max << " mAh\n";
                for(int i=0; i<s; i++)
                {
                    for(int j=0; j<(p-1); j++)
                        tries << bat[i][j] << ", ";

                    tries << bat[i][p-1] << std::endl;
                }
                tries << std::endl;
                tries.close();
            }
        }
    }

    for(int i=0; i<s; i++)
    {
        for(int j=0; j<(p-1); j++)
            std::cout << bat[i][j] << ", ";

        std::cout << bat[i][p-1] << std::endl;
    }

    std::ofstream pack("pack.txt");
    if (pack.is_open())
    {
        pack << dc << ". delta: " << delta << " mAh\n";
        for(int i=0; i<s; i++)
        {
            for(int j=0; j<(p-1); j++)
                pack << bat[i][j] << ", ";

            pack << bat[i][p-1] << std::endl;
        }
        pack.close();
    }

    std::ofstream check("check.txt");
    if (check.is_open())
    {
        check << dc << ". delta: " << delta << " mAh\n";
        for(int i=0; i<s; i++)
        {
            for(int j=0; j<(p-1); j++)
                check << bat[i][j] << "+";

            check << bat[i][p-1] << " = " << sum[i] << " mAh" << std::endl;
        }
        check.close();
    }

    return 0;
}
