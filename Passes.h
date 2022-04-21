#include "Team.h"

int expectedPasses();

int* calculatePassesEachMinute(int expected_half, int mins_per_half);

int passesThisMinute(int min, int* vec, int mins_per_half);

void distributePasses(const int passes_min, const int possession_home, int& passes_home, const int possession_away, int& passes_away);

int getPasser(const Team& team);

int distributePasses(Team& team, const int passes_nr);
