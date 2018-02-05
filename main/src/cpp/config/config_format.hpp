#pragma once

struct ConfigFormat {
  struct Executors {
    static constexpr auto Field = "executors";

    static constexpr auto name = "name";
    static constexpr auto command = "command";
    static constexpr auto parser = "parser";
    static constexpr auto validator = "validator";
  };
};
