/*
*	Adapted from Princess Of Sleeping's PUP extractor
*	https://github.com/Princess-of-Sleeping/PSV-PUP-Extractor
*/

#include "pup.h"
int psvDebugScreenPrintf(const char *format, ...);
void psvDebugScreenClear();

int NotExistMkdir(char *path){

	int dfd = sceIoDopen(path);
	if(dfd >= 0){

		sceIoDclose(dfd);

	}else{

		sceIoMkdir(path, 0777);

	}

	return 0;

}


int scePlayStartionUpdatePackageExtractStage1(char *ext_pup_path) {
	SceUID file_check = sceIoOpen(ext_pup_path, SCE_O_RDONLY, 0);
	if(file_check < 0){
		return file_check;
	}

	ScePlayStartionUpdatePackageHeader1 header;
	sceIoPread(file_check, &header, sizeof(ScePlayStartionUpdatePackageHeader1), 0);
	sceIoPread(file_check, temp_buff, sizeof(temp_buff), 0);

	if(BYTE_SWAP_64(header.magic) != 0x5343455546000001){
		return -1;
	}

	sceGetPlayStartionUpdatePackageInfo(&header);

	sprintf(pup_dec_dir, "ur0:/pup_out/");
	NotExistMkdir(pup_dec_dir);

	for(int i=0;i<header.file_count;i++){
		scePlayStartionUpdatePackageExtractFiles(pup_dec_dir, file_check, i, header.file_count, temp_buff);
	}
	sceIoClose(file_check);
	return 0;
}

int sceGetPlayStartionUpdatePackageType(int pup_type){

	memset(pup_type_buf, 0, sizeof(pup_type_buf));

	switch (pup_type){

		case 4:sprintf(pup_type_buf, "TestKit");break;
		//case 3:sprintf(pup_type_buf, "???\n");break;
		case 2:sprintf(pup_type_buf, "Retail");break;
		case 1:sprintf(pup_type_buf, "DevKit");break;

		default:sprintf(pup_type_buf, "unknown");break;

	}

	return 0;

}

int sceGetPlayStartionUpdatePackageInfo(ScePlayStartionUpdatePackageHeader1 *header){
	sceGetPlayStartionUpdatePackageType(header->pup_type);
	return 0;

}


void sceGetPlayStartionUpdatePackageFileEntryId(void *buff, int entry_id){
	switch (entry_id) {

			case 0x100:sprintf(buff, "version.txt");break;
			case 0x101:sprintf(buff, "license.xml");break;
			case 0x200:sprintf(buff, "psp2swu.self");break;
			case 0x204:sprintf(buff, "cui_setupper.self");break;

			case 0x221:sprintf(buff, "psv_package_data01.pkg");break;
			case 0x231:sprintf(buff, "psv_package_data02.pkg");break;

			case 0x301:sprintf(buff, "package_data01.pkg");break;
			case 0x302:sprintf(buff, "package_data02.pkg");break;
			case 0x303:sprintf(buff, "package_data03.pkg");break;
			case 0x304:sprintf(buff, "package_data04.pkg");break;
			case 0x305:sprintf(buff, "package_data05.pkg");break;
			case 0x306:sprintf(buff, "package_data06.pkg");break;
			case 0x307:sprintf(buff, "package_data07.pkg");break;
			case 0x308:sprintf(buff, "package_data08.pkg");break;
			case 0x309:sprintf(buff, "package_data09.pkg");break;
			case 0x30A:sprintf(buff, "package_data10.pkg");break;
			case 0x30B:sprintf(buff, "package_data11.pkg");break;
			case 0x30C:sprintf(buff, "package_data12.pkg");break;
			case 0x30D:sprintf(buff, "package_data13.pkg");break;
			case 0x30E:sprintf(buff, "package_data14.pkg");break;
			case 0x30F:sprintf(buff, "package_data15.pkg");break;
			case 0x310:sprintf(buff, "package_data16.pkg");break;
			case 0x311:sprintf(buff, "package_data17.pkg");break;
			case 0x312:sprintf(buff, "package_data18.pkg");break;
			case 0x313:sprintf(buff, "package_data19.pkg");break;
			case 0x314:sprintf(buff, "package_data20.pkg");break;
			case 0x315:sprintf(buff, "package_data21.pkg");break;
			case 0x316:sprintf(buff, "package_data22.pkg");break;
			case 0x317:sprintf(buff, "package_data23.pkg");break;
			case 0x318:sprintf(buff, "package_data24.pkg");break;
			case 0x319:sprintf(buff, "package_data25.pkg");break;
			case 0x31A:sprintf(buff, "package_data26.pkg");break;

			case 0x31B:sprintf(buff, "unknown_0x31B");break;
			case 0x31C:sprintf(buff, "unknown_0x31C");break;
			case 0x31D:sprintf(buff, "unknown_0x31D");break;
			case 0x31E:sprintf(buff, "unknown_0x31E");break;
			case 0x31F:sprintf(buff, "unknown_0x31F");break;
			case 0x320:sprintf(buff, "unknown_0x320");break;
			case 0x321:sprintf(buff, "unknown_0x321");break;
			case 0x322:sprintf(buff, "unknown_0x322");break;
			case 0x323:sprintf(buff, "unknown_0x323");break;
			case 0x324:sprintf(buff, "unknown_0x324");break;
			case 0x325:sprintf(buff, "unknown_0x325");break;

			case 0x326:sprintf(buff, "debug_data00.pkg");break;
			case 0x327:sprintf(buff, "debug_data01.pkg");break;
			case 0x328:sprintf(buff, "debug_data02.pkg");break;
			case 0x329:sprintf(buff, "debug_data03.pkg");break;
			case 0x32A:sprintf(buff, "debug_data04.pkg");break;
			case 0x32B:sprintf(buff, "debug_data05.pkg");break;
			case 0x32C:sprintf(buff, "debug_data06.pkg");break;

			case 0x32D:sprintf(buff, "unknown_0x32D");break;
			case 0x32E:sprintf(buff, "unknown_0x32E");break;
			case 0x32F:sprintf(buff, "unknown_0x32F");break;
			case 0x330:sprintf(buff, "unknown_0x330");break;
			case 0x331:sprintf(buff, "unknown_0x331");break;
			case 0x332:sprintf(buff, "unknown_0x332");break;
			case 0x333:sprintf(buff, "unknown_0x333");break;
			case 0x334:sprintf(buff, "unknown_0x334");break;
			case 0x335:sprintf(buff, "unknown_0x335");break;
			case 0x336:sprintf(buff, "unknown_0x336");break;
			case 0x337:sprintf(buff, "unknown_0x337");break;
			case 0x338:sprintf(buff, "unknown_0x338");break;

			case 0x400:sprintf(buff, "package_scewm.wm");break;
			case 0x401:sprintf(buff, "package_sceas.as");break;


			default:{

				sprintf(buff, "unknown_0x%X", entry_id);

			}

	}
	psvDebugScreenPrintf("Extracting ur0:/pup_out/%s\n",(char*)buff);
}


char pup_buffer[0x20000];

int scePlayStartionUpdatePackageExtractFiles(char *pup_dec_dir, SceUID file_check, int i, SceUInt32 file_count, void *header){

	char write_file_name[0x100];
	char write_file_path[0x200];

	uint32_t base_addr1 = 0x80 + (0x20 * i);
	uint32_t base_addr2 = (0x80 + (0x20 * file_count)) + (0x40 * i);

	ScePlayStartionUpdatePackageHeader2 header2;
	ScePlayStartionUpdatePackageHeader3 header3;

	sceIoPread(file_check, &header2, sizeof(ScePlayStartionUpdatePackageHeader2), base_addr1);
	sceIoPread(file_check, &header3, sizeof(ScePlayStartionUpdatePackageHeader3), base_addr2);

	sceGetPlayStartionUpdatePackageFileEntryId(write_file_name, header2.entry_id);

	sprintf(write_file_path, "%s%s", pup_dec_dir, write_file_name);

	int fd = sceIoOpen(write_file_path, SCE_O_TRUNC | SCE_O_CREAT | SCE_O_WRONLY, 0777);


	if(fd < 0){
		return fd;
	}


	uint32_t plus_address = 0x0, read_size = sizeof(pup_buffer);

	do {

		if((plus_address + sizeof(pup_buffer)) > header2.data_length){

			read_size = (plus_address + sizeof(pup_buffer)) - header2.data_length;

			read_size = sizeof(pup_buffer) - read_size;

		}

		int sipr = sceIoPread(file_check, pup_buffer, read_size, header2.data_offset + plus_address);

		sceIoWrite(fd, pup_buffer, sipr);

		plus_address += sizeof(pup_buffer);

	} while (plus_address < header2.data_length);



	sceIoClose(fd);


	return 0;

}

