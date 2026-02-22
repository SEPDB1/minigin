#pragma once
#include <cassert>
#include <memory>
#include "GameObject.h"

namespace dae
{
	namespace test
	{
		static void TestSceneGraph()
		{
			auto pParent1 = std::make_unique<GameObject>();
			auto pChild1 = std::make_unique<GameObject>();
			auto pGrandChild1 = std::make_unique<GameObject>();
			auto pParent2 = std::make_unique<GameObject>();
			auto pChild2 = std::make_unique<GameObject>();
			auto pGrandChild2 = std::make_unique<GameObject>();

			pChild1->SetParent(pChild1.get());
			// should stay nullptr
			assert(pChild1->GetParent() == nullptr);

			// set valid parent
			pChild1->SetParent(pParent1.get());
			// Did set work?
			assert(pChild1->GetParent() == pParent1.get());
			// Is child in the list?
			assert(pParent1->GetChildAt(0) == pChild1.get());
			// Does the count match the previous actions?
			assert(pParent1->GetChildCount() == 1);

			pChild1->SetParent(nullptr);
			// Does setting no parent work?
			assert(pChild1->GetParent() == nullptr);
			// Did the child get removed?
			assert(pParent1->GetChildCount() == 0);

			pChild1->SetParent(pParent1.get());
			pChild2->SetParent(pParent1.get());
			// Do multiple children work?
			assert(pChild1->GetParent() == pParent1.get() && pChild2->GetParent() == pParent1.get());
			// Does it return the last created child?
			assert(pParent1->GetChildAt(1) == pChild2.get());
			// Does the count match?
			assert(pParent1->GetChildCount() == 2);

			pGrandChild1->SetParent(pChild1.get());
			//assert(pGrandChild1->IsParent(pParent1.get()));
			//assert(!pGrandChild1->IsParent(nullptr));
			//assert(!pGrandChild1->IsParent(pGrandChild1.get()));
			//assert(pParent1->IsChild(pGrandChild1.get()));
			//assert(!pParent1->IsChild(nullptr));
			//assert(!pParent1->IsChild(pParent1.get()));

			pChild1->SetParent(pParent2.get());
			assert(pParent1->GetChildCount() == 1);
			assert(pChild1->GetParent() == pParent2.get());

			pChild2->SetParent(nullptr);
			assert(pChild2->GetParent() == nullptr);
			assert(pParent1->GetChildCount() == 0);
		}
	}
}