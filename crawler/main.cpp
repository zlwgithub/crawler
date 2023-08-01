#include"service.h"
#include<vector>
#include<iostream>

#include <gzip/compress.hpp>
#include <gzip/config.hpp>
#include <gzip/decompress.hpp>
#include <gzip/utils.hpp>
#include <gzip/version.hpp>

int main()
{
	//std::string url = "https://place.qyer.com";
	//cpr::Response r = cpr::Get(cpr::Url(url));

	//const char* compressed_pointer = r.text.data();
	//std::string decompressed_data = gzip::decompress(compressed_pointer, r.text.size());

	//writeintfile("./a.txt", decompressed_data, true, true);

	CrawlService::getInstance();



	while (1)
	{

	}

}