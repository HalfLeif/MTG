#pragma once

#include "../core/library.h"

inline Library kTHB = Library::Builder()
                          .SetLimited()
                          .AddCard(MakeCard("G", 1, "MossViper"))
                          .AddCard(MakeCard("G", 1, "Spider"))

                          .AddCard(MakeCard("WG", 1, "BronzehideLion"))
                          .AddCard(MakeCard("1G", 1, "Beetle"))
                          .AddCard(MakeCard("1G", 0, "Warbriar"))
                          .AddCard(MakeCard("1W", 0, "IndomitableWill"))

                          .AddCard(MakeCard("2W", 1, "FavoredOfIroas"))
                          .AddCard(MakeCard("2G", 1, "NyxHerald"))
                          .AddCard(MakeCard("2G", 1, "Champion"))
                          .AddCard(MakeCard("2W", 0, "DreadfulApathy"))
                          .AddCard(MakeCard("2W", 0, "BanishingLight"))
                          .AddCard(MakeCard("3", 0, "EntrancingLyre"))

                          .AddCard(MakeCard("3W", 1, "Pegasus"))
                          .AddCard(MakeCard("2GG", 1, "Typhon"))
                          .AddCard(MakeCard("2GG", 1, "Typhon"))
                          .AddCard(MakeCard("2GG", 5, "Renata"))
                          .AddCard(MakeCard("3G", 0, "Mantle"))
                          .AddCard(MakeCard("3W", 0, "TriumphantSurge"))
                          .AddCard(MakeCard("2WW", 0, "Intervention"))

                          .AddCard(MakeCard("4G", 1, "Forerunner"))
                          .AddCard(MakeCard("4GG", 1, "Pheres"))
                          .AddCard(MakeCard("3GGG", 1, "Colossus"))
                          .AddCard(MakeCard("3WW", 0, "Elspeth"))

                          .AddLand(Shore(), Experiment::exp)
                          .Build();
