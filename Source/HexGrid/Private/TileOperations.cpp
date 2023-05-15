// Fill out your copyright notice in the Description page of Project Settings.

#include "TileOperations.h"
#include <algorithm>
#include "Algo/Reverse.h"

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

TArray<FIntPoint> UTileOperations::FindPathAStar(const FIntPoint& Source, const FIntPoint& Target, const TMap<FIntPoint, int32>& MovementCosts)
{
    // Structure representing a vertex in the graph
    struct FNode
    {
        FIntPoint Position;
        int32 GScore;
        int32 FScore;
        FIntPoint Parent;

        FNode(const FIntPoint& InPosition, int32 InGScore, int32 InFScore, const FIntPoint& InParent)
            : Position(InPosition), GScore(InGScore), FScore(InFScore), Parent(InParent) {}
    };

    // Checking if Source and Target are different points
    if (Source == Target)
    {
        TArray<FIntPoint> EmptyPath;
        return EmptyPath;
    }

    // List of open and closed vertices
    TArray<FIntPoint> OpenSet;
    TSet<FIntPoint> ClosedSet;

    // Map of vertices with their FScore
    TMap<FIntPoint, int32> FScoreMap;

    // Adding Source to the list of open vertices
    OpenSet.Add(Source);
    FScoreMap.Add(Source, FMath::Abs(Source.X - Target.X) + FMath::Abs(Source.Y - Target.Y));

    // Map of vertices with their GScore
    TMap<FIntPoint, int32> GScoreMap;
    GScoreMap.Add(Source, 0);

    TMap<FIntPoint, FNode> FNodeMap;

    // While there are still vertices to be checked
    while (OpenSet.Num() > 0)
    {
        // Selecting the vertex with the lowest FScore
        FIntPoint Current = OpenSet[0];
        int32 LowestFScore = FScoreMap[Current];
        for (const FIntPoint& OpenNode : OpenSet)
        {
            if (FScoreMap[OpenNode] < LowestFScore)
            {
                Current = OpenNode;
                LowestFScore = FScoreMap[OpenNode];
            }
        }

        // If we have reached the goal, reconstruct the path
        if (Current == Target)
        {
            TArray<FIntPoint> Path;
            while (Current != Source)
            {
                Path.Add(Current);
                Current = FNodeMap[Current].Parent;
            }
            Path.Add(Source);
            Algo::Reverse(Path);
            return Path;
        }

        // Removing the current vertex from the open list
        OpenSet.Remove(Current);

        // Adding it to the closed list of vertices
        ClosedSet.Add(Current);

        // Checking neighboring vertices
        TArray<FIntPoint> Neighbours = GetAdjacentTileNeighbours(Current);
        for (const FIntPoint& Neighbour : Neighbours)
        {
            // If the neighboring vertex is already closed, we skip it
            if (ClosedSet.Contains(Neighbour))
            {
                continue;
            }

            if (!MovementCosts.Contains(Neighbour))
            {
                continue;
            }
            // Calculating the GScore cost for the neighbor
            int32 GScore = GScoreMap[Current] + MovementCosts[Neighbour];

            // If the neighboring vertex is not yet open, we add it to the list of open vertices
            if (!OpenSet.Contains(Neighbour))
            {
                OpenSet.Add(Neighbour);
            }
            // If the new GScore is higher than the previous one, we skip this neighbor
            else if (GScore >= GScoreMap[Neighbour])
            {
                continue;
            }

            // Updating the GScore and FScore for the neighbor
            GScoreMap.Add(Neighbour, GScore);
            int32 FScore = GScore + FMath::Abs(Neighbour.X - Target.X) + FMath::Abs(Neighbour.Y - Target.Y);;
            FScoreMap.Add(Neighbour, FScore);

            // Updating the parent information for the neighbor
            FNodeMap.Add(Neighbour, FNode(Neighbour, GScore, FScore, Current));
        }
    }

    // If the path could not be found, we return an empty array
    TArray<FIntPoint> EmptyPath;
    return EmptyPath;
}