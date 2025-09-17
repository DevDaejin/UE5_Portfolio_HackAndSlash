#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "BasicPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;

UCLASS()
class PF_HACKANDSLASH_API ABasicPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	UPROPERTY(EditDefaultsOnly, Category="입력")
	UInputMappingContext* PlayerMappingContext;

	UPROPERTY(EditDefaultsOnly, Category="입력")
	UInputAction* MoveIA;

private:
	void InputMove(const FInputActionValue& value);
};
