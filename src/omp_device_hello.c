#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
//g mancini sept 18

int main()
{
    #pragma omp target teams
    {
        int host     = omp_is_initial_device();
        int nthreads = omp_get_num_threads();
        int nteams   = omp_get_num_teams();
        int ndev     = omp_get_num_devices();
        int def      = omp_get_default_device();
        printf("Host=%d nthreads=%d nteams=%d ndev=%d default dev=%d\n",host, 
            nthreads, nteams, ndev, def);
        int team = omp_get_team_num();
        printf("I am team %d\n",team);
    }
    
    return 0;
}