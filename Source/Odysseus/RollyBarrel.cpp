// Has literally no use except to fufill assignment specs

#include "PhysicsEngine/RadialForceComponent.h"
#include "RollyBarrel.h"

// Sets default values
ARollyBarrel::ARollyBarrel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BarrelMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BarrelMesh"));
	BarrelMesh->SetupAttachment(RootComponent);
	BarrelMesh->SetSimulatePhysics(true);
	//ForceComp set up
	ForceComponent = CreateDefaultSubobject<URadialForceComponent>(TEXT("ForceComponent"));
	ForceComponent->SetupAttachment(BarrelMesh);
}

// Called when the game starts or when spawned
void ARollyBarrel::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARollyBarrel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//BarrelMesh->AddForce(GetActorUpVector() * ForceAmount * BarrelMesh->GetMass());//Adds Force to Barrel every frame. Not needed, just for reference material incase I make some more physics objects.
}

