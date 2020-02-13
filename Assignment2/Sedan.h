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
		Sedan(const Sedan& copy);
		virtual ~Sedan();

		bool AddTrailer(const Trailer* trailer);
		bool RemoveTrailer();

		// Vehicle��(��) ���� ��ӵ�
		virtual unsigned int GetMaxSpeed() const override;

		// Vehicle��(��) ���� ��ӵ�
		virtual void Travel() override;

		// IDrivable��(��) ���� ��ӵ�
		virtual unsigned int GetDriveSpeed() const override;

	private:
		const Trailer* mTrailer;
	};
}