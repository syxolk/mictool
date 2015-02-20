#include <gtest/gtest.h>
#include <cli/cli.h>

TEST(CLI, inputFileAndOutputFile) {
    const char *argv[] = {"mictool", "input.mpr", "--output", "output.html"};
    CLI cli(4, argv);
    cli.parse();

    EXPECT_EQ(CLI::OutputType::HTML, cli.format());
    EXPECT_FALSE(cli.isReadFromStdIn());
    EXPECT_FALSE(cli.isWriteToStdOut());
    EXPECT_EQ("input.mpr", cli.input());
    EXPECT_EQ("output.html", cli.output());
    EXPECT_FALSE(cli.quiet());
}

TEST(CLI, inputFileAndStdout) {
    const char *argv[] = {"mictool", "input.mpr", "--latex"};
    CLI cli(3, argv);
    cli.parse();

    EXPECT_EQ(CLI::OutputType::LATEX, cli.format());
    EXPECT_FALSE(cli.isReadFromStdIn());
    EXPECT_TRUE(cli.isWriteToStdOut());
    EXPECT_EQ("input.mpr", cli.input());
    EXPECT_FALSE(cli.quiet());
}

TEST(CLI, stdinAndOutputFile) {
    const char *argv[] = {"mictool", "-o", "output.tex"};
    CLI cli(3, argv);
    cli.parse();

    EXPECT_EQ(CLI::OutputType::LATEX, cli.format());
    EXPECT_TRUE(cli.isReadFromStdIn());
    EXPECT_FALSE(cli.isWriteToStdOut());
    EXPECT_EQ("output.tex", cli.output());
    EXPECT_FALSE(cli.quiet());
}

TEST(CLI, stdinAndStdout) {
    const char *argv[] = {"mictool", "--debug", "--quiet"};
    CLI cli(3, argv);
    cli.parse();

    EXPECT_EQ(CLI::OutputType::DEBUG, cli.format());
    EXPECT_TRUE(cli.isReadFromStdIn());
    EXPECT_TRUE(cli.isWriteToStdOut());
    EXPECT_TRUE(cli.quiet());
}
