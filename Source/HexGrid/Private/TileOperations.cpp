// Fill out your copyright notice in the Description page of Project Settings.

#include "TileOperations.h"
#include <algorithm>


TArray<FIntPoint> UTileOperations::GetTileNeighboursInRange(const FIntPoint& SourceTile, int Radius)
{
    TArray<FIntPoint> Neighbours;
    int n = Radius;
    Neighbours = GetAdjacentTileNeighbours(SourceTile);

    // Iteratively find unique neighbors within the given radius
    for (int i = 0; i < n - 1; i++)
    {
        TArray<FIntPoint> UniqueNeighbours;

        // Check neighbors of existing tiles
        for (int j = 0; j < Neighbours.Num(); j++)
        {
            TArray<FIntPoint> LocalNeighbours = GetAdjacentTileNeighbours(Neighbours[j]);

            // Check if each neighbor is unique and add it to the list if it is
            for (const FIntPoint& Neighbour : LocalNeighbours) {
                if (!Neighbours.Contains(Neighbour)) {
                    UniqueNeighbours.Add(Neighbour);
                }
            }
        }

        // Add the unique neighbors to the existing list
        Neighbours.Append(UniqueNeighbours);
    }

    // Log the number of neighbors found within the range
    UE_LOG(LogTemp, Warning, TEXT("Found %d neighbors in range of %d"), Neighbours.Num(), n);

    return Neighbours;
}

TArray<FIntPoint> UTileOperations::GetAdjacentTileNeighbours(const FIntPoint& SourceTile)
{
    TArray<FIntPoint> Neighbours;
    int x = SourceTile.X;
    int y = SourceTile.Y;

    // Check if x is an even number
    if (x % 2 == 0) {
        // If x is even, add the neighbors accordingly
        Neighbours.Add(FIntPoint(x, y - 1));
        Neighbours.Add(FIntPoint(x, y + 1));
        Neighbours.Add(FIntPoint(x - 1, y));
        Neighbours.Add(FIntPoint(x + 1, y));
        Neighbours.Add(FIntPoint(x - 1, y - 1));
        Neighbours.Add(FIntPoint(x + 1, y - 1));
    }
    else {
        // If x is odd, add the neighbors accordingly
        Neighbours.Add(FIntPoint(x, y - 1));
        Neighbours.Add(FIntPoint(x, y + 1));
        Neighbours.Add(FIntPoint(x - 1, y));
        Neighbours.Add(FIntPoint(x + 1, y));
        Neighbours.Add(FIntPoint(x - 1, y + 1));
        Neighbours.Add(FIntPoint(x + 1, y + 1));
    }

    return Neighbours;
}
