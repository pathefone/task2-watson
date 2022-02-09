map = Map("rutx-watson")

--credentials section
section = map:section(NamedSection, "identity", "rutx-watson", "Watson Credentials", "Enter your Watson IBM IOT user account credentials to establish connection")

orgId = section:option(Value, "orgId", "orgId")
typeId = section:option(Value, "typeId", "typeId")
deviceId = section:option(Value, "deviceId", "deviceId")

flag = section:option(Flag, "enabled", "Enable", "Select to enable watson datasender")

--token section
token_section = map:section(NamedSection, "auth", "rutx-watson", "Authentication token", "Enter your token to authenticate with Watson IBM IOT")

token = token_section:option(Value, "token", "token")
token.datatype = "string"
token.maxlength = 30;
token.password = true;

return map
