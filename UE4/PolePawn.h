#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/WorldSettings.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Networking.h"
#include "Async/Async.h"
#include "Sockets.h"
#include "Camera/CameraComponent.h"

#include "PolePawn.generated.h"

UCLASS()
class POLEBALANCING2_API APolePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APolePawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	bool IsConnectionOpen = false;
	bool WaitingForConnection = false;

	bool HasInput = false;
	bool AppliedInput = false;
	int Input_ = 0;

	TFuture<void> ClientConnectionFinishedFuture;

public:	

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Base;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UStaticMeshComponent* Pole;

	UPROPERTY(EditAnywhere)
	USceneComponent* PoleController;

	UPROPERTY(EditAnywhere)
		USceneComponent* Cam;

	UPROPERTY(EditAnywhere)
		USceneComponent* _BaseComponent;

	UPROPERTY(EditAnywhere)
		float MaxSpeed;

	UPROPERTY(EditAnywhere)
		float XBoundary;

	UPROPERTY(EditAnywhere)
		float MotorPower;

	UPROPERTY(EditAnywhere)
		float CurrMotorSpeed;

	UPROPERTY(EditAnywhere)
		AWorldSettings* WorldSettings;

	UFUNCTION(BlueprintImplementableEvent)
 		void OnPause();

	UFUNCTION(BlueprintImplementableEvent)
 		void OnResume();

	void Move_XAxis(float AxisValue);

	void Open_Connection();
	void Close_Connection();
	void Conduct_Connection();
	void Reset_Env();

	float Timer = 0;

	FSocket* ListenSocket;
	FSocket* ConnectionSocket;
};
