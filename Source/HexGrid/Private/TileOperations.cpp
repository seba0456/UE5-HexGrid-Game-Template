// Fill out your copyright notice in the Description page of Project Settings.


#include "TileOperations.h"
#include <algorithm>

TArray<FIntPoint> UTileOperations::GetTileNeighbours(const FIntPoint& SourceTile, int Radius)
{
	TArray<FIntPoint> Neighbours;
	int x = SourceTile.X;
	int y = SourceTile.Y;
    for (int i = -Radius; i <= Radius; i++)
    {
        for (int j = std::max(-Radius, -i - Radius); j <= std::min(Radius, -i + Radius); j++) {
            int z = -i - j;
            // Exclude the center point (x, y) from the list of neighbors
            if (!((x + i) == x && (y + j == y))) {
                // Add the neighbor coordinates to the list of neighborsd
                Neighbours.Add(FIntPoint(x + i, y + j));
            }
        }
    }
	return Neighbours;
}

TArray<FIntPoint> UTileOperations::GetAdjacentTileNeighbours(const FIntPoint& SourceTile)
{
    TArray<FIntPoint> Neighbours;
    int x = SourceTile.X;
    int y = SourceTile.Y;
    Neighbours.Add(FIntPoint(x + 1, y));
    UE_LOG(LogTemp, Warning, TEXT("The integer value is: %d , %d"), x + 1, y);
    Neighbours.Add(FIntPoint(x + 1, y + 1));
    Neighbours.Add(FIntPoint(x, y-1));
    Neighbours.Add(FIntPoint(x, y+1));
    Neighbours.Add(FIntPoint(x - 1, y));
    Neighbours.Add(FIntPoint(x - 1, y + 1));
    return Neighbours;
}



