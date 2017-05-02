// Fill out your copyright notice in the Description page of Project Settings.

#include "ArenaBattle.h"
#include "ABGameInstance.h"

// ������ �����Ͻ�
UABGameInstance::UABGameInstance()
{
	UE_LOG(LogTemp, Warning, TEXT("ABGameInstance constructor!"));

	WebConnect = CreateDefaultSubobject<UWebConnect>(TEXT("WebConnect")); // CreateDefaultSubobject�� �����ڿ����� �� �� �ִ�. CDO
}

// ��Ÿ�ӿ� ���� ���� �ε�
void UABGameInstance::Init()
{
	AB_LOG_CALLONLY(Warning)
	Super::Init();


	// UWebConnect�� uasset���Ϸ� ����
	FString PackageName = TEXT("/Temp/SavedWebConnection");
	UPackage* NewPackage = CreatePackage(nullptr, *PackageName);
	WebConnect2= NewObject<UWebConnect>(NewPackage);
	FString PackageFileName = FPackageName::LongPackageNameToFilename(PackageName, FPackageName::GetAssetPackageExtension());

	WebConnect2->Host = TEXT("127.0.0.7");
	WebConnect2->URI = TEXT("/");
	if (UPackage::SavePackage(NewPackage, WebConnect2, RF_Standalone, *PackageFileName))
	{
		UPackage* SavedPackage = ::LoadPackage(NULL, *PackageFileName, LOAD_None);
		TArray<UObject *> ObjectsInPackage;
		GetObjectsWithOuter(SavedPackage, ObjectsInPackage, false);
		for (const auto& EachObject : ObjectsInPackage)
		{
			UWebConnect* WebConnectionFromFile = Cast<UWebConnect>(EachObject);
			if (WebConnectionFromFile)
			{
				AB_LOG(Warning, TEXT("WebConnection From File : Host %s , URI %s"), *WebConnectionFromFile->Host, *WebConnectionFromFile->URI);
			}
		}
	}



	// �ø���������̼�
	/*
	WebConnect2 = NewObject<UWebConnect>(this);
	WebConnect2->Host = TEXT("127.0.0.7");
	WebConnect2->URI = TEXT("/");
	AB_LOG(Warning, TEXT("Outer Class Name : %s"), *WebConnect2->GetOuter()->GetClass()->GetName());
	AB_LOG(Warning, TEXT("Outermost Class Name : %s"), *WebConnect2->GetOutermost()->GetClass()->GetName());

	FString FullPath = FString::Printf(TEXT("%s%s"), *FPaths::GameSavedDir(), TEXT("WebConnection.txt"));
	FArchive* ArWriter = IFileManager::Get().CreateFileWriter(*FullPath);
	if (ArWriter)
	{
		*ArWriter << *WebConnect2;

		ArWriter->Close();
		delete ArWriter;
		ArWriter = NULL;
	}

	TSharedPtr<FArchive> FileReader = MakeShareable(IFileManager::Get().CreateFileReader(*FullPath));
	if (FileReader.IsValid())
	{
		UWebConnect* WebConnectionFromFile = NewObject<UWebConnect>(this);
		*FileReader.Get() << *WebConnectionFromFile;
		FileReader->Close();
		AB_LOG(Warning, TEXT("WebConnect From File : Host %s , URI %s"), *WebConnectionFromFile->Host, *WebConnectionFromFile->URI);
	}
	*/

	// ��������Ʈ
	/*
	FHouse* HouseNew = new FHouse();

	WebConnect->TokenCompleteDelegate.AddDynamic(this, &UABGameInstance::RequestTokenComplete);
	WebConnect->TokenCompleteDelegate.AddDynamic(this, &UABGameInstance::RequestTokenComplete2);
	//WebConnect->TokenCompleteDelegate.AddRaw(HouseNew, &FHouse::RequestTokenComplete);

	WebConnect->RequestToken(TEXT("destiny"));
	*/

	// ��Ÿ
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

	#pragma region ������ �ǽ�
	/*
	// 1�ܰ�
	AB_LOG(Warning, TEXT("****** 1�ܰ� ******"));
	FHouse* NewHouseAddress = new FHouse();
	AB_LOG(Warning, TEXT("���� ���� �������ϴ�. ����ũ�� : %d"), NewHouseAddress->Size);
	if (NewHouseAddress)
	{
		delete NewHouseAddress;
		AB_LOG(Warning, TEXT("���� ���� ���� ö���߽��ϴ�. ��ũ�� : %d"), NewHouseAddress->Size);
		NewHouseAddress = nullptr;
	}

	// 2�ܰ�
	AB_LOG(Warning, TEXT("****** 2�ܰ� ******"));
	NewHouseAddress = new FHouse();
	NewHouseAddress->Size = 100;
	AB_LOG(Warning, TEXT("���� �ٽ� �������ϴ�. ��ũ�� : %d"), NewHouseAddress->Size);
	{
		TUniquePtr<FHouse> MyHouseDeed = TUniquePtr<FHouse>(NewHouseAddress);
		if (MyHouseDeed.IsValid())
		{
			AB_LOG(Warning, TEXT("�� ���� �� �ܵ����� �����Դϴ�. ����ũ�� : %d"), MyHouseDeed->Size);
		}

		//TUniquePtr<FHouse> FriendsHouseDeed = MyHouseDeed;  // ������ ����! �ܵ� ������ ����
		TUniquePtr<FHouse> FriendsHouseDeed = MoveTemp(MyHouseDeed); // ���� �״�� �ΰ� �����θ� ����
		if (!MyHouseDeed.IsValid())
		{
			AB_LOG(Warning, TEXT("ģ������ ���� �Ⱦҽ��ϴ�. ģ����ũ�� : %d"), FriendsHouseDeed->Size);
		}
	}
	AB_LOG(Warning, TEXT("�������� ������� ���� �ڵ����� ö�ŵǾ����ϴ�. ��ũ�� : %d"), NewHouseAddress->Size);

	// 3�ܰ�
	AB_LOG(Warning, TEXT("****** 3�ܰ� ******"));
	NewHouseAddress = new FHouse();
	NewHouseAddress->Size = 150.0f;
	AB_LOG(Warning, TEXT("���� �� �ٽ� �������ϴ�. ��ũ�� : %d"), NewHouseAddress->Size);
	{
		TSharedPtr<FHouse> MyHouseDeed = MakeShareable(NewHouseAddress); // ������� ���� ���Ŀ� ���
		if (MyHouseDeed.IsValid())
		{
			AB_LOG(Warning, TEXT("���� ���� ������ ���� �Ǿ����ϴ�. ����ũ�� : %d"), MyHouseDeed->Size);
			if (MyHouseDeed.IsUnique())
			{
				AB_LOG(Warning, TEXT("����� ȥ�� �����ϰ� �ֽ��ϴ�. ����ũ�� : %d"), MyHouseDeed->Size);
			}
		}

		TSharedPtr<FHouse> FriendsHouseDeed = MyHouseDeed;
		if (!FriendsHouseDeed.IsUnique())
		{
			AB_LOG(Warning, TEXT("ģ���� ���� ���������� �Ǿ����ϴ�. ģ����ũ�� : %d"), FriendsHouseDeed->Size);
		}

		MyHouseDeed.Reset(); // ���� �� �������� ������
		if (FriendsHouseDeed.IsUnique())
		{
			AB_LOG(Warning, TEXT("���� ģ���� ���� �����ϰ� �ֽ��ϴ�. ģ����ũ�� : %d"), FriendsHouseDeed->Size);
		}

		AB_LOG(Warning, TEXT("���� ���� �״�� �ֽ��ϴ�. ��ũ�� : %d"), NewHouseAddress->Size);
	}

	AB_LOG(Warning, TEXT("���� �ڵ� ö�ŵǾ����ϴ�. ��ũ�� : %d"), NewHouseAddress->Size);


	// 4�ܰ�
	AB_LOG(Warning, TEXT("****** 4�ܰ� ******"));
	NewHouseAddress = new FHouse();
	NewHouseAddress->Size = 200.0f;
	AB_LOG(Warning, TEXT("���� �ѹ� �� �ٽ� �������ϴ�. ù��°��ũ�� : %d"), NewHouseAddress->Size);

	FHouse* NewHouseAddress2 = new FHouse();
	NewHouseAddress2->Size = 250.0f;
	AB_LOG(Warning, TEXT("ģ���� ���� ���� �������ϴ�. �ι�°��ũ�� : %d"), NewHouseAddress2->Size);

	{
		TSharedPtr<FHouse> MyHouseDeed = MakeShareable(NewHouseAddress);
		AB_LOG(Warning, TEXT("�� ���� ���� �����մϴ�. ����ũ�� : %d"), MyHouseDeed->Size);
		TSharedPtr<FHouse> FriendsHouseDeed = MakeShareable(NewHouseAddress2);
		AB_LOG(Warning, TEXT("ģ�� ���� ģ���� �����մϴ�. ģ����ũ�� : %d"), FriendsHouseDeed->Size);

		MyHouseDeed->OthersDeed = FriendsHouseDeed;
		AB_LOG(Warning, TEXT("ģ�� ���� ���� �����ϰ� ������ �� ���� �����մϴ�. ģ����ũ�� : %d"), MyHouseDeed->OthersDeed->Size);
		FriendsHouseDeed->OthersDeed = MyHouseDeed;
		AB_LOG(Warning, TEXT("ģ���� �� ���� ���� �����ϰ� ������ �ڱ� ���� �����մϴ�. ����ũ�� : %d"), FriendsHouseDeed->OthersDeed->Size);
	}

	AB_LOG(Warning, TEXT("�������� ������� ���� ���� ���� �ڵ� ö�ŵ��� �ʽ��ϴ�. ù��°��ũ�� : %d"), NewHouseAddress->Size);
	AB_LOG(Warning, TEXT("ģ���� ���� ���� �ڵ� ö�ŵ��� �ʽ��ϴ�. �ι�°��ũ�� : %d"), NewHouseAddress2->Size);

	NewHouseAddress->OthersDeed.Reset();
	AB_LOG(Warning, TEXT("ģ���� ���� ���� �������� ö���߽��ϴ�. ���ּҰ� �����־ �����Դϴ�. �ι�°��ũ�� : %d"), NewHouseAddress2->Size);
	AB_LOG(Warning, TEXT("�������� ���� ���� ���� �ڵ� ö�ŵ˴ϴ�. ù��°��ũ�� : %d"), NewHouseAddress->Size);

	// 5�ܰ�
	AB_LOG(Warning, TEXT("****** 5�ܰ� ******"));
	NewHouseAddress = new FHouse();
	NewHouseAddress->Size = 300.0f;
	AB_LOG(Warning, TEXT("���� ���������� ���� �����ϴ�. ù��°��ũ�� : %d"), NewHouseAddress->Size);

	NewHouseAddress2 = new FHouse();
	NewHouseAddress2->Size = 350.0f;
	AB_LOG(Warning, TEXT("ģ���� ���� �ٽ� �������ϴ�. �ι�°��ũ�� : %d"), NewHouseAddress2->Size);

	{
		TSharedPtr<FHouse> MyHouseDeed = MakeShareable(NewHouseAddress);
		AB_LOG(Warning, TEXT("�� ���� ���� �����մϴ�. ����ũ�� : %d"), MyHouseDeed->Size);
		TSharedPtr<FHouse> FriendsHouseDeed = MakeShareable(NewHouseAddress2);
		AB_LOG(Warning, TEXT("ģ�� ���� ģ���� �����մϴ�. ģ����ũ�� : %d"), FriendsHouseDeed->Size);

		MyHouseDeed->OthersDeed = FriendsHouseDeed;
		AB_LOG(Warning, TEXT("ģ�� ���� ���� �����ϰ� ������ �� ���� �����մϴ�. ģ����ũ�� : %d"), MyHouseDeed->OthersDeed->Size);
		FriendsHouseDeed->AccessHouse = MyHouseDeed;
		AB_LOG(Warning, TEXT("ģ���� �� �� ������ �����մϴ�. ����ũ�� : %d"), FriendsHouseDeed->AccessHouse.Pin()->Size);
	}

	AB_LOG(Warning, TEXT("���� ���� ���� �ڵ� ö�ŵ˴ϴ�. ù��°��ũ�� : %d"), NewHouseAddress->Size);
	AB_LOG(Warning, TEXT("ģ���� ���� ���� �ڵ� ö�ŵ˴ϴ�. �ι�°��ũ�� : %d"), NewHouseAddress2->Size);


	// 6�ܰ�
	AB_LOG(Warning, TEXT("****** 6�ܰ� ******"));
	WebConnect2 = NewObject<UWebConnect>();
	WebConnect2->Host = TEXT("127.0.0.1");
	//WebConnect2->AddToRoot();
	WebConnect2->ConditionalBeginDestroy();
	//GetWorld()->ForceGarbageCollection(true);
	GetWorld()->GetTimerManager().SetTimer(ObjectCheckTimer, this, &UABGameInstance::CheckUObjectAlive, 1.0f, true);
	*/
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
		AB_LOG(Warning, TEXT("�𸮾������Ʈ�� ���Դϴ�."));
		return;
	}

	if (!WebConnect2->IsValidLowLevel())
	{
		AB_LOG(Warning, TEXT("�𸮾������Ʈ�� ��ȿ���� �ʽ��ϴ�."));
		return;
	}

	AB_LOG(Warning, TEXT("�𸮾������Ʈ�� ���� ����ֽ��ϴ�. : %s"), *WebConnect2->Host);
}