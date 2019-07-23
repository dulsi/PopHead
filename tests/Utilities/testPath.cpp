#include "Utilities/path.hpp"
#include "catch.hpp"
#include <string>

namespace ph {

TEST_CASE("is filepath properly converted to module name", "[Utilities][Path]")
{
	std::string audioModuleFilePath = PH_PATH_SEPARATOR + std::string("PopHead") + PH_PATH_SEPARATOR + "src" + PH_PATH_SEPARATOR + "Audio" + PH_PATH_SEPARATOR;
	std::string inputModuleFilePath = PH_PATH_SEPARATOR + std::string("PopHead") + PH_PATH_SEPARATOR + "src" + PH_PATH_SEPARATOR + "Input" + PH_PATH_SEPARATOR;
	std::string utilitiesModuleFilePath = PH_PATH_SEPARATOR + std::string("PopHead") + PH_PATH_SEPARATOR + "src" + PH_PATH_SEPARATOR + "Utilities" + PH_PATH_SEPARATOR;
	std::string noneFilePath = PH_PATH_SEPARATOR + std::string("PopHead") + PH_PATH_SEPARATOR + "src" + PH_PATH_SEPARATOR + "main.cpp";

	CHECK(Path::toModuleName(audioModuleFilePath) == "Audio");
	CHECK(Path::toModuleName(inputModuleFilePath) == "Input");
	CHECK(Path::toModuleName(utilitiesModuleFilePath) == "Utilities");
	CHECK(Path::toModuleName(noneFilePath) == "None");
}

TEST_CASE("is filepath properly converted to file name", "[Utilities][Path]")
{
	std::string terminalFilePath = PH_PATH_SEPARATOR + std::string("PopHead") + PH_PATH_SEPARATOR + "src" + PH_PATH_SEPARATOR + "Terminal" + PH_PATH_SEPARATOR + "terminal.cpp";
	std::string rendererFilePath = PH_PATH_SEPARATOR + std::string("PopHead") + PH_PATH_SEPARATOR + "src" + PH_PATH_SEPARATOR + "Renderer" + PH_PATH_SEPARATOR + "renderer.cpp";
	std::string musicPlayerFilePath = PH_PATH_SEPARATOR + std::string("PopHead") + PH_PATH_SEPARATOR + "src" + PH_PATH_SEPARATOR + "Audio" + PH_PATH_SEPARATOR + "Music" + 
		PH_PATH_SEPARATOR + "musicPlayer.cpp";

	CHECK(Path::toFilename(terminalFilePath) == "terminal.cpp");
	CHECK(Path::toFilename(rendererFilePath) == "renderer.cpp");
	CHECK(Path::toFilename(musicPlayerFilePath) == "musicPlayer.cpp");
}

TEST_CASE("are exceptions called properly", "[Utilities][Path]")
{

	std::string nonexistentFilePath = PH_PATH_SEPARATOR+ std::string("PopHead") + PH_PATH_SEPARATOR + "github" + PH_PATH_SEPARATOR + "git" + PH_PATH_SEPARATOR;
	std::string duplicatedFilePath = PH_PATH_SEPARATOR + std::string("PopHead") + PH_PATH_SEPARATOR + "src" + PH_PATH_SEPARATOR + "PopHead" + PH_PATH_SEPARATOR + "src";
	std::string incompleteFilePath = PH_PATH_SEPARATOR + std::string("PopHead") + PH_PATH_SEPARATOR +"src" + PH_PATH_SEPARATOR;

	SECTION("lack of module") {
		CHECK_THROWS(Path::toModuleName(nonexistentFilePath));
	}
	SECTION("duplicated path") {
		CHECK_THROWS(Path::toModuleName(duplicatedFilePath));
	}
	SECTION("incomplete path") {
		CHECK_THROWS(Path::toModuleName(incompleteFilePath));
	}

}
}
