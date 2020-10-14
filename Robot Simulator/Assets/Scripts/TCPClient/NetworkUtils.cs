using System;
using System.Collections.Generic;
using System.Net;
using System.Net.Sockets;
using System.Linq;

public class NetworkUtils 
{
    /// <summary>
    /// Find your IP address
    /// </summary>
    /// <returns>The local ip address</returns>
    public static IEnumerable<string> GetLocalIpAddress()
    {
        IPAddress[] ipAdresses = Dns.GetHostEntry(Dns.GetHostName()).AddressList;
        return from ip in ipAdresses where ip.AddressFamily == AddressFamily.InterNetwork select ip.ToString();
    }


    /// <summary>
    /// Get router gateway
    /// </summary>
    /// <returns>The default gateway in string form</returns>
    public static IEnumerable<string> GetDefaultGateway()
    {
        return from ip in GetLocalIpAddress() select ip.Substring(0, ip.LastIndexOf(".", StringComparison.Ordinal)).Insert(ip.LastIndexOf(".", StringComparison.Ordinal), ".1");
    }


    /// <summary>
    /// Sort by last number
    /// </summary>
    /// <param name="ipaddress"></param>
    /// <returns></returns>
    public static IEnumerable<string> SortByLastNumber(IEnumerable<string> ipaddress)
    {
        return ipaddress.OrderBy(i => i.Remove(0, i.LastIndexOf(".", StringComparison.Ordinal)));
    }


    /// <summary>
    /// Get local ip address without the last digit number (192.168.1.24 -> 192.168.1)
    /// </summary>
    /// <returns></returns>
    private static IEnumerable<string> GetLocalIpAddressWithoutLastDigit()
    {
        return from ip in GetLocalIpAddress() select ip.Substring(0, ip.LastIndexOf(".", StringComparison.Ordinal));
    }


    /// <summary>
    /// Scan all local ip address
    /// For example :(from 192.168.1.1 to 192.168.1.255)
    /// </summary>
    /// <param name="rangeScan">Ip address range has end at 255. So you can set less if you want</param>
    /// <returns>Returns a list for all local addresses</returns>
    public static List<IPAddress> GetAllIpAddresses(ushort rangeScan = 255)
    {
        if (rangeScan > 255)
        {
            throw  new ArgumentException($"{nameof(rangeScan)} can not be above 255");
        }

        List<IPAddress> result = new List<IPAddress>();
        foreach (string ip in SortByLastNumber(GetLocalIpAddressWithoutLastDigit()))
        {
            for (int i = 1; i <= rangeScan; i++)
            {
                result.Add(IPAddress.Parse($"{ip}.{i}"));
            }
        }
        return result;
    }
}
