// Fill out your copyright notice in the Description page of Project Settings.

#include "ArenaBattle.h"
#include "ABGameInstance.h"

// 에디터 컴파일시
UABGameInstance::UABGameInstance()
{
	UE_LOG(LogTemp, Warning, TEXT("ABGameInstance constructor!"));

	WebConnect = CreateDefaultSubobject<UWebConnect>(TEXT("WebConnect")); // CreateDefaultSubobject는 생성자에서만 쓸 수 있다. CDO
}

// 런타임에 가장 먼저 로딩
void UABGameInstance::Init()
{
	AB_LOG_CALLONLY(Warning)
	Super::Init();

	FHouse* HouseNew = new FHouse();

	WebConnect->TokenCompleteDelegate.AddUObject(this, &UABGameInstance::RequestTokenComplete);
	WebConnect->TokenCompleteDelegate.AddUObject(this, &UABGameInstance::RequestTokenComplete2);
	WebConnect->TokenCompleteDelegate.AddRaw(HouseNew, &FHouse::RequestTokenComplete);

	WebConnect->RequestToken(TEXT("destiny"));

	/*
	UE_LOG(LogClass, Warning, TEXT("GameInstance Init!"));

	WebConnect2 = NewObject<UWebConnect>(this);

	UClass* ClassInfo1 = WebConnect->GetClass();
	UClass* ClassInfo2 = UWebConnect::StaticClass();
	if (ClassInfo1 == ClassInfo2)
	{
		AB_LOG(Warning, TEXT("ClassInfo1 is same with ClassInfo2"));
	}

	for (TFieldIterator<UProperty> It(ClassInfo1); It; ++It)
	{
		AB_LOG(Warning, TEXT("Field : %s, Type : %s"), *It->GetName(), *It->GetClass()->GetName());

		UStrProperty* StrProp = FindField<UStrProperty>(ClassInfo1, *It->GetName());
		if (StrProp)
		{
			AB_LOG(Warning, TEXT("Value = %s"), *StrProp->GetPropertyValue_InContainer(WebConnect));
		}
	}

	for (const auto& Entry : ClassInfo1->NativeFunctionLookupTable)
	{
		AB_LOG(Warning, TEXT("Function = %s"), *Entry.Name.ToString());
		UFunction* Func1 = ClassInfo1->FindFunctionByName(FName(TEXT("RequestToken")));
		if (Func1->ParmsSize == 0)
		{
			WebConnect->ProcessEvent(Func1, NULL);
		}
	}

	WebConnect3 = NewObject<UWebConnect>(this);
	AB_LOG(Warning, TEXT("Outer of NewObject : %s"), *WebConnect3->GetOuter()->GetClass()->GetFullName());

	UWorld* CurrentWorld = GetWorld();
	for (const auto& Entry : FActorRange(CurrentWorld))
	{
		AB_LOG(Warning, TEXT("Actor : %s"), *Entry->GetName());
		TArray<UObject* > Components;
		Entry->GetDefaultSubobjects(Components);
		for (const auto& CEntry : Components)
		{
			AB_LOG(Warning, TEXT(" -- Component : %s"), *CEntry->GetName());
		}
	}

	for (TActorIterator<AStaticMeshActor> It(CurrentWorld); It; ++It)
	{
		AB_LOG(Warning, TEXT("StaticMesh Actor : %s"), *It->GetName());
	}
	*/

	#pragma region 포인터 실습
	// 1단계
	AB_LOG(Warning, TEXT("****** 1단계 ******"));
	FHouse* NewHouseAddress = new FHouse();
	AB_LOG(Warning, TEXT("집을 새로 지었습니다. 내집크기 : %d"), NewHouseAddress->Size);
	if (NewHouseAddress)
	{
		delete NewHouseAddress;
		AB_LOG(Warning, TEXT("내가 직접 집을 철거했습니다. 집크기 : %d"), NewHouseAddress->Size);
		NewHouseAddress = nullptr;
	}

	// 2단계
	AB_LOG(Warning, TEXT("****** 2단계 ******"));
	NewHouseAddress = new FHouse();
	NewHouseAddress->Size = 100;
	AB_LOG(Warning, TEXT("집을 다시 지었습니다. 집크기 : %d"), NewHouseAddress->Size);
	{
		TUniquePtr<FHouse> MyHouseDeed = TUniquePtr<FHouse>(NewHouseAddress);
		if (MyHouseDeed.IsValid())
		{
			AB_LOG(Warning, TEXT("이 집은 제 단독소유 주택입니다. 내집크기 : %d"), MyHouseDeed->Size);
		}

		//TUniquePtr<FHouse> FriendsHouseDeed = MyHouseDeed;  // 컴파일 에러! 단독 소유만 가능
		TUniquePtr<FHouse> FriendsHouseDeed = MoveTemp(MyHouseDeed); // 집은 그대로 두고 집주인만 변경
		if (!MyHouseDeed.IsValid())
		{
			AB_LOG(Warning, TEXT("친구에게 집을 팔았습니다. 친구집크기 : %d"), FriendsHouseDeed->Size);
		}
	}
	AB_LOG(Warning, TEXT("집문서가 사라져서 집은 자동으로 철거되었습니다. 집크기 : %d"), NewHouseAddress->Size);

	// 3단계
	AB_LOG(Warning, TEXT("****** 3단계 ******"));
	NewHouseAddress = new FHouse();
	NewHouseAddress->Size = 150.0f;
	AB_LOG(Warning, TEXT("집을 또 다시 지었습니다. 집크기 : %d"), NewHouseAddress->Size);
	{
		TSharedPtr<FHouse> MyHouseDeed = MakeShareable(NewHouseAddress); // 만들어진 집을 차후에 등록
		if (MyHouseDeed.IsValid())
		{
			AB_LOG(Warning, TEXT("공동 소유 가능한 집이 되었습니다. 내집크기 : %d"), MyHouseDeed->Size);
			if (MyHouseDeed.IsUnique())
			{
				AB_LOG(Warning, TEXT("현재는 혼자 소유하고 있습니다. 내집크기 : %d"), MyHouseDeed->Size);
			}
		}

		TSharedPtr<FHouse> FriendsHouseDeed = MyHouseDeed;
		if (!FriendsHouseDeed.IsUnique())
		{
			AB_LOG(Warning, TEXT("친구와 집을 나눠가지게 되었습니다. 친구집크기 : %d"), FriendsHouseDeed->Size);
		}

		MyHouseDeed.Reset(); // 내가 집 소유권을 포기함
		if (FriendsHouseDeed.IsUnique())
		{
			AB_LOG(Warning, TEXT("이제 친구만 집을 소유하고 있습니다. 친구집크기 : %d"), FriendsHouseDeed->Size);
		}

		AB_LOG(Warning, TEXT("집은 아직 그대로 있습니다. 집크기 : %d"), NewHouseAddress->Size);
	}

	AB_LOG(Warning, TEXT("집은 자동 철거되었습니다. 집크기 : %d"), NewHouseAddress->Size);


	// 4단계
	AB_LOG(Warning, TEXT("****** 4단계 ******"));
	NewHouseAddress = new FHouse();
	NewHouseAddress->Size = 200.0f;
	AB_LOG(Warning, TEXT("집을 한번 더 다시 지었습니다. 첫번째집크기 : %d"), NewHouseAddress->Size);

	FHouse* NewHouseAddress2 = new FHouse();
	NewHouseAddress2->Size = 250.0f;
	AB_LOG(Warning, TEXT("친구도 집을 직접 지었습니다. 두번째집크기 : %d"), NewHouseAddress2->Size);

	{
		TSharedPtr<FHouse> MyHouseDeed = MakeShareable(NewHouseAddress);
		AB_LOG(Warning, TEXT("내 집은 내가 소유합니다. 내집크기 : %d"), MyHouseDeed->Size);
		TSharedPtr<FHouse> FriendsHouseDeed = MakeShareable(NewHouseAddress2);
		AB_LOG(Warning, TEXT("친구 집은 친구가 소유합니다. 친구집크기 : %d"), FriendsHouseDeed->Size);

		MyHouseDeed->OthersDeed = FriendsHouseDeed;
		AB_LOG(Warning, TEXT("친구 집을 공동 소유하고 문서를 내 집에 보관합니다. 친구집크기 : %d"), MyHouseDeed->OthersDeed->Size);
		FriendsHouseDeed->OthersDeed = MyHouseDeed;
		AB_LOG(Warning, TEXT("친구도 내 집을 공동 소유하고 문서를 자기 집에 보관합니다. 내집크기 : %d"), FriendsHouseDeed->OthersDeed->Size);
	}

	AB_LOG(Warning, TEXT("집문서가 사라져도 내가 지은 집이 자동 철거되지 않습니다. 첫번째집크기 : %d"), NewHouseAddress->Size);
	AB_LOG(Warning, TEXT("친구가 지은 집도 자동 철거되지 않습니다. 두번째집크기 : %d"), NewHouseAddress2->Size);

	NewHouseAddress->OthersDeed.Reset();
	AB_LOG(Warning, TEXT("친구가 지은 집을 수동으로 철거했습니다. 집주소가 남아있어서 다행입니다. 두번째집크기 : %d"), NewHouseAddress2->Size);
	AB_LOG(Warning, TEXT("이제서야 내가 지은 집도 자동 철거됩니다. 첫번째집크기 : %d"), NewHouseAddress->Size);

	// 5단계
	AB_LOG(Warning, TEXT("****** 5단계 ******"));
	NewHouseAddress = new FHouse();
	NewHouseAddress->Size = 300.0f;
	AB_LOG(Warning, TEXT("이제 마지막으로 집을 짓습니다. 첫번째집크기 : %d"), NewHouseAddress->Size);

	NewHouseAddress2 = new FHouse();
	NewHouseAddress2->Size = 350.0f;
	AB_LOG(Warning, TEXT("친구도 집을 다시 지었습니다. 두번째집크기 : %d"), NewHouseAddress2->Size);

	{
		TSharedPtr<FHouse> MyHouseDeed = MakeShareable(NewHouseAddress);
		AB_LOG(Warning, TEXT("내 집은 내가 소유합니다. 내집크기 : %d"), MyHouseDeed->Size);
		TSharedPtr<FHouse> FriendsHouseDeed = MakeShareable(NewHouseAddress2);
		AB_LOG(Warning, TEXT("친구 집은 친구가 소유합니다. 친구집크기 : %d"), FriendsHouseDeed->Size);

		MyHouseDeed->OthersDeed = FriendsHouseDeed;
		AB_LOG(Warning, TEXT("친구 집을 공동 소유하고 문서를 내 집에 보관합니다. 친구집크기 : %d"), MyHouseDeed->OthersDeed->Size);
		FriendsHouseDeed->AccessHouse = MyHouseDeed;
		AB_LOG(Warning, TEXT("친구가 내 집 정보를 열람합니다. 내집크기 : %d"), FriendsHouseDeed->AccessHouse.Pin()->Size);
	}

	AB_LOG(Warning, TEXT("내가 지은 집은 자동 철거됩니다. 첫번째집크기 : %d"), NewHouseAddress->Size);
	AB_LOG(Warning, TEXT("친구가 지은 집도 자동 철거됩니다. 두번째집크기 : %d"), NewHouseAddress2->Size);


	// 6단계
	AB_LOG(Warning, TEXT("****** 6단계 ******"));
	WebConnect2 = NewObject<UWebConnect>();
	WebConnect2->Host = TEXT("127.0.0.1");
	//WebConnectionNew->AddToRoot();
	WebConnect2->ConditionalBeginDestroy();
	//GetWorld()->ForceGarbageCollection(true);
	GetWorld()->GetTimerManager().SetTimer(ObjectCheckTimer, this, &UABGameInstance::CheckUObjectAlive, 1.0f, true);
	#pragma endregion
}


void UABGameInstance::RequestTokenComplete(const FString& Token)
{
	AB_LOG(Warning, TEXT("Token : %s"), *Token);
}

void UABGameInstance::RequestTokenComplete2(const FString& Token)
{
	AB_LOG(Warning, TEXT("Token : %s"), *Token);
}


void UABGameInstance::CheckUObjectAlive()
{
	if (!WebConnect2)
	{
		AB_LOG(Warning, TEXT("언리얼오브젝트가 널입니다."));
		return;
	}

	if (!WebConnect2->IsValidLowLevel())
	{
		AB_LOG(Warning, TEXT("언리얼오브젝트가 유효하지 않습니다."));
		return;
	}

	AB_LOG(Warning, TEXT("언리얼오브젝트가 아직 살아있습니다. : %s"), *WebConnect2->Host);
}