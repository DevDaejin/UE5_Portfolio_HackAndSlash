#include "BasicPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/Character.h"

void ABasicPlayerController::BeginPlay()
{
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		if (PlayerMappingContext)
		{
			Subsystem->AddMappingContext(PlayerMappingContext, 0);
		}
	}
}

void ABasicPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(InputComponent))
	{
		if (MoveIA)
		{
			EIC->BindAction(MoveIA, ETriggerEvent::Triggered, this, &ABasicPlayerController::InputMove);
		}
	}
}

void ABasicPlayerController::InputMove(const FInputActionValue& value)
{
	const FVector2D InputVector = value.Get<FVector2D>();

	if (APawn* PlayerPawn = GetPawn())
	{
		const FVector Forward = FVector::ForwardVector;
		const FVector Right = FVector::RightVector;

		FVector MoveDir = (Forward * InputVector.Y) + (Right * InputVector.X);
		MoveDir.Normalize();

		if (!MoveDir.IsNearlyZero())
		{
			PlayerPawn->AddMovementInput(MoveDir);

			FRotator TargetRot = MoveDir.Rotation();
			FRotator CurrentRot = PlayerPawn->GetActorRotation();
			FRotator smooth = FMath::RInterpTo(CurrentRot, TargetRot, GetWorld()->GetDeltaSeconds(), 10);

			PlayerPawn->SetActorRotation(smooth);
		}
	}
}
