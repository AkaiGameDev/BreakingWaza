// Fill out your copyright notice in the Description page of Project Settings.


#include "AlchemyCircleActor.h"

AAlchemyCircleActor::AAlchemyCircleActor()
{
	// Create and set up a sphere component as the root component
	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));
	RootComponent = CollisionComponent;

	// Set up the collision parameters
	CollisionComponent->SetCollisionProfileName(TEXT("Trigger"));
	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AAlchemyCircleActor::OnOverlapBegin);
}

void AAlchemyCircleActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AItem* Ingredient = Cast<AItem>(OtherActor);
	if (!Ingredient)
		return;

	//if(Ingredient)
}
