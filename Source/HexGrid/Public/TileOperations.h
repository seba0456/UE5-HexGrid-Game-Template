#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include <vector>
#include <utility>
#include "TileOperations.generated.h"

/**
 *
 */
UCLASS()
class HEXGRID_API UTileOperations : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
        UFUNCTION(BlueprintCallable, Category = "Tile Operations")
        static TArray<FIntPoint> GetTileNeighboursInRange(const FIntPoint& SourceTile, int Radius);
        
    UFUNCTION(BlueprintCallable, Category = "Tile Operations", meta = (DisplayName = "Get Adjacent Tile Neighbours", Description = "A function that returns tile neighbours."))
        static TArray<FIntPoint> GetAdjacentTileNeighbours(const FIntPoint& SourceTile);
    
};


