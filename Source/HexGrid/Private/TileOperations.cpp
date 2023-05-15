// Fill out your copyright notice in the Description page of Project Settings.


#include "TileOperations.h"
#include <algorithm>


TArray<FIntPoint> UTileOperations::GetTileNeighboursInRange(const FIntPoint& SourceTile, int Radius)
{
    TArray<FIntPoint> Neighbours;
    int n = Radius;
    Neighbours = GetAdjacentTileNeighbours(SourceTile);

    for (int i = 0; i < n - 1; i++)
    {
        TArray<FIntPoint> UniqueNeighbours;
        for (int j = 0; j < Neighbours.Num(); j++)
        {
            TArray<FIntPoint> LocalNeighbours = GetAdjacentTileNeighbours(Neighbours[j]);
            for (const FIntPoint& Neighbour : LocalNeighbours) {
                if (!Neighbours.Contains(Neighbour)) {
                    UniqueNeighbours.Add(Neighbour);
                }
            }
        }
        Neighbours.Append(UniqueNeighbours);
    }
    UE_LOG(LogTemp, Warning, TEXT("Found %d neightbours in range of %d"), Neighbours.Num(),n);
    return Neighbours;
}


TArray<FIntPoint> UTileOperations::GetAdjacentTileNeighbours(const FIntPoint& SourceTile)
{
    TArray<FIntPoint> Neighbours;
    int x = SourceTile.X;
    int y = SourceTile.Y;
    if (x % 2 == 0) {
        Neighbours.Add(FIntPoint(x, y - 1));
        Neighbours.Add(FIntPoint(x, y + 1));
        Neighbours.Add(FIntPoint(x - 1, y));
        Neighbours.Add(FIntPoint(x + 1, y));
        Neighbours.Add(FIntPoint(x - 1, y - 1));
        Neighbours.Add(FIntPoint(x + 1, y - 1));
    }
    else {
        Neighbours.Add(FIntPoint(x, y - 1));
        Neighbours.Add(FIntPoint(x, y + 1));
        Neighbours.Add(FIntPoint(x - 1, y));
        Neighbours.Add(FIntPoint(x + 1, y));
        Neighbours.Add(FIntPoint(x - 1, y + 1));
        Neighbours.Add(FIntPoint(x + 1, y + 1));
    }
    
    return Neighbours;
}











