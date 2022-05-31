// See https://aka.ms/new-console-template for more information


using System.Reflection;

Assembly SampleAssembly = Assembly.LoadFrom
    (@"D:\repoditory\OS\desktop\lab3\test\test\libs\liblibrary.dll");

Console.WriteLine(SampleAssembly.GetName());
foreach (Type oType in SampleAssembly.GetTypes())
{
    Console.WriteLine(oType.Name);

    foreach(MemberInfo members in oType.GetMembers())
    {
        Console.WriteLine("    " + members.Name);
    }
    Console.WriteLine();
}