#pragma once

namespace Pow
{
	uint32_t pow(uint32_t num)
	{
		switch(num)
		{
		case 0:
			return 1;
			break;
		case 1:
			return 2;
			break;
		case 2:
			return 4;
			break;
		case 3:
			return 8;
			break;
		case 4:
			return 16;
			break;
		case 5:
			return 32;
			break;
		case 6:
			return 64;
			break;
		case 7:
			return 128;
			break;
		case 8:
			return 256;
			break;
		case 9:
			return 512;
			break;
		case 10:
			return 1024;
			break;
		case 11:
			return 2048;
			break;
		case 12:
			return 4096;
			break;
		case 13:
			return 8192;
			break;
		case 14:
			return 16384;
			break;
		case 15:
			return 32768;
			break;
		case 16:
			return 65536;
			break;
		case 17:
			return 131072;
			break;
		case 18:
			return 262144;
			break;
		case 19:
			return 524288;
			break;
		case 20:
			return 1048576;
			break;
		case 21:
			return 2097152;
			break;
		case 22:
			return 4194304;
			break;
		case 23:
			return 8388608;
			break;
		case 24:
			return 16777216;
			break;
		case 25:
			return 33554432;
			break;
		case 26:
			return 67108864;
			break;
		case 27:
			return 134217728;
			break;
		case 28:
			return 268435456;
			break;
		case 29:
			return 536870912;
			break;
		case 30:
			return 1073741824;
			break;
		case 31:
			return 2147483648;
			break;
		default:
			return -1;
			break;
		}
	}

}