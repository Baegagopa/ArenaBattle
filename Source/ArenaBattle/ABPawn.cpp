// Fill out your copyright notice in the Description page of Project Settings.

#include "ArenaBattle.h"
#include "ABGameInstance.h"
#include "ABPawn.h"


// Sets default values
AABPawn::AABPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Body = CreateDefaultSubobject < UCapsuleComponent>(TEXT("Body"));
	RootComponent = Body;

	Mesh = CreateDefaultSubobject < USkeletalMeshComponent>(TEXT("Mash"));
	Mesh->SetupAttachment(Body);

	Movement = CreateDefaultSubobject < UFloatingPawnMovement>(TEXT("Movement"));
	Camera = CreateDefaultSubobject < UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(Body);

	Body->SetCapsuleHalfHeight(88.0f);
	Body->SetCapsuleRadius(34.0f);

	Mesh->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -88.0f), FRotator(0.0f, -90.0f, 0.0f));
	Camera->SetRelativeLocationAndRotation(FVector(-195.0f, 0.0f, 57.0f), FRotator(-10.0f, 0.0f, 0.0f));
	
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_Mesh(TEXT("SkeletalMesh'/Game/InfinityBladeWarriors/Character/CompleteCharacters/SK_CharM_Bladed.SK_CharM_Bladed'"));
	Mesh->SetSkeletalMesh(SK_Mesh.Object);
	MaxHP = 100.0f;
	this->AutoPossessPlayer = EAutoReceiveInput::Player0;
}

// Called when the game starts or when spawned
void AABPawn::BeginPlay()
{
	Super::BeginPlay();
	CurrentHP = MaxHP;

	int32 NewIndex = FMath::RandRange(0, CharacterAssets.Num() - 1);
	UABGameInstance* ABGameInstance = Cast<UABGameInstance>(GetGameInstance());
	if (ABGameInstance)
	{
		TAssetPtr<USkeletalMesh> NewCharacter = Cast<USkeletalMesh>(ABGameInstance->AssetLoader.SynchronousLoad(CharacterAssets[NewIndex]));
		if (NewCharacter)
		{
			Mesh->SetSkeletalMesh(NewCharacter.Get());
		}
	}
}

// Called every frame
void AABPawn::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void AABPawn::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

