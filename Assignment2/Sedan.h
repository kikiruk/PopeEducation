#pragma once
#include "Vehicle.h"
#include "IDrivable.h"
#include "Trailer.h"

namespace assignment2
{
	class Trailer;

	class Sedan : public Vehicle, IDrivable
	{
	public:
		Sedan();
		virtual ~Sedan();

		const Sedan& operator=(const Sedan& other);

		bool AddTrailer(const Trailer* trailer);
		bool RemoveTrailer();

		// Vehicle을(를) 통해 상속됨
		virtual unsigned int GetMaxSpeed() const override;

		// Vehicle을(를) 통해 상속됨
		virtual void Travel() override;

		// IDrivable을(를) 통해 상속됨
		virtual unsigned int GetDriveSpeed() const override;

	private:
		const Trailer* mTrailer;
	};
}