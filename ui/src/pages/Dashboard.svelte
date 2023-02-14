<script>
    import { onMount } from "svelte";

    onMount(async () => {
        fetch("/api/settings")
            .then((response) => {
                console.log(response);
                return response.json();
            })
            .then((data) => {
                console.log(data);
                ip = data["ip"];
                ssid = data["ssid"];
                mac = data["mac"];
                version = data["version"];
            });
    });

    export let ip;
    export let ssid;
    export let mac;
    export let version;

    export let delProgress = false;

    function settingsResetClick() {
        delProgress = true;
        fetch("/api/settings/reset")
            .then((response) => {
                console.log(response);
                return response.json();
            })
            .then((data) => {
                alert(
                    "Beállítások törölve, az eszköz újraindul. Az eszköz újrapárosításra vár."
                );
                delProgress = false;
            });
    }
</script>

<div class="card">
    <header>Dashboard</header>
    <table>
        <tr>
            <th>Firmware version</th>
            <td>{version}</td>
        </tr>
        <tr>
            <th>IP address</th>
            <td>{ip}</td>
        </tr>
        <tr>
            <th>SSID</th>
            <td>{ssid}</td>
        </tr>
        <tr>
            <th>MAC</th>
            <td>{mac}</td>
        </tr>
    </table>

    <footer class="is-right">
        <button on:click={settingsResetClick} aria-busy={delProgress}>
            Reset to factory settings
        </button>
    </footer>
</div>
